
----------------------------------
--     INITIALIZE XP_DEMO       --
----------------------------------
function XP_initialize()
    -- initialization

    -- Declare ports
    blobs_port = yarp.BufferedPortBottle()
    ispeak_port = yarp.BufferedPortBottle()
    acteff_port = yarp.Port()
    speechRecog_port = yarp.Port()

    --rpc
    toolinc_rpc = yarp.RpcClient()
    tmanager_rpc = yarp.RpcClient()
    affcollect_rpc = yarp.RpcClient()
    are_rpc = yarp.RpcClient()
    are_cmd = yarp.RpcClient()
    are_get = yarp.RpcClient()
    wholebody_rpc = yarp.RpcClient()

    -- DEFINES

    TOOL_SELECTION_FLAG = false;

    -- Declare consts.
    OBJECT_MEMORY       = 0.5       -- seconds
    SENSITIVITY         = 0.8       -- 80 percent
    X_GRASP_OFFSET      = 0.05      -- m it will reach towards the robot from the estimated 3D position
    Y_GRASP_OFFSET      = 0.02      -- m it will reach to the right of the estimated 3D position
    Z_GRASP_OFFSET      = 0.03      -- m it will reach above of the estimated 3D position
    Z_OBJECT_OFFSET     = 0.02      -- grasp objects from 4 cm above table (z+=0.04)

    -- LIMIT LINES
    MIN_X = -0.6        -- meter
    MAX_X = -0.1
    MIN_Y = -0.4
    MAX_Y = 0.25
    CENTER_X = -0.41
    CENTER_Y = 0.05

    -- ZONES (in order of priority)
    ZONES_LIST = {"BOTTOMLEFT", "BOTTOMRIGHT", "UPRIGHT", "UPLEFT", "OUT"}

    -- UPRIGHT
    UPRIGHT_ZONE_X = {min=MIN_X, max=CENTER_X}
    UPRIGHT_ZONE_Y = {min=CENTER_Y, max=MAX_Y}

    -- UPLEFT
    UPLEFT_ZONE_X = {min=MIN_X, max=CENTER_X}
    UPLEFT_ZONE_Y = {min=MIN_Y, max=CENTER_Y}

    --BOTTOMRIGHT
    BOTTOMRIGHT_ZONE_X = {min=CENTER_X, max=MAX_X}
    BOTTOMRIGHT_ZONE_Y = {min=CENTER_Y, max=MAX_Y}

    --BOTTOMLEFT
    REACHABLE_ZONE_X  = {min=CENTER_X, max=MAX_X}
    REACHABLE_ZONE_Y  = {min=MIN_Y, max=CENTER_Y}

    -- ACTION LIST
    TASK_LIST = {"no_act", "drag_down", "drag_left", "drag_diag_left", "drag_right", "drag_diag_right", "take_hand", "drag_left_hand"}

    TOOL_LIST = {"HOE1", "HOK1", "RAK2", "SHO3", "STI3"}


    tool_list_grammar = {HOE1 = "hoe", HOK3 = "hook", RAK2 = "rake", SHO3 = "shovel", STI3 = "stick"}

    -- defining speech grammar for Reward
    -- grammar_reward = "Yes you are | No here it is | Skip it"

    -- Read tool action list
    TOOL_ACTIONS = get_act_labels()
    if TOOL_ACTIONS ~= nil then
       print("Action labels set properly ")
       for key,value in pairs(TOOL_ACTIONS) do print(key,value) end

    else
       print("Prbolems setting action labels ")
    end

    object_list = {}                               -- for keeping the memory of objects
    target_object = {}                             -- targeted object

    -- initalize flags;
    cleanTableSec = 0
    tooFarSaid = false
    holdingTool = false
    tableClean = false

    state = "observe"

    return true
end



----------------------------------
--     LOCALIZE  OBJECTS        --
----------------------------------

--/---------------------------------------------------------------------/
function find(object_list, item)
    for key, value in pairs(object_list) do
        if overlap(item, value) == true then return key end
    end
    return nil
end

function overlap(object1, object2)
    dist = math.sqrt(math.pow(object1.u-object2.u, 2) + math.pow(object1.v-object2.v, 2))
    if dist < 5.0 then return true end
    return false
end

function leaky_integrate(object_list, blobs, t_now)
    -- update object list
    for i=0,blobs:size()-1 do
        obj = blobs:get(i):asList()
        c_x = (obj:get(2):asDouble() + obj:get(0):asDouble()) / 2.0
        c_y = (obj:get(3):asDouble() + obj:get(1):asDouble()) / 2.0
        if find(object_list, {u=c_x, v=c_y}) == nil then
            table.insert(object_list, {u=c_x, v=c_y, w=0, t=t_now, x=0, y=0, z=0, task = "none"})
        end
    end

    --Checking("print stability")
    for key, value in pairs(object_list) do        
        is_overlaped = false
        for i=0,blobs:size()-1 do
            obj = blobs:get(i):asList()
            c_x = (obj:get(2):asDouble() + obj:get(0):asDouble()) / 2.0
            c_y = (obj:get(3):asDouble() + obj:get(1):asDouble()) / 2.0
            if overlap(value, {u=c_x, v=c_y}) == true then
                is_overlaped = true
                break;
            end
        end
        if is_overlaped == true then
            -- with 30fps after 2s it reaches the threshold 1.0
            value.w = value.w + 0.03
            if value.w > (2.0-SENSITIVITY) then value.w = 2.0-SENSITIVITY end
            value.t = t_now
        else
            value.w = value.w - (t_now-value.t)/OBJECT_MEMORY
        end
        print("Blob " .. key .. " has stability value of " .. value.w ) 
    end
end

function forget_expired_objects()
    for i=#object_list,1,-1 do
        if object_list[i].w < 0.0 then table.remove(object_list, i) end
    end
end


function get_stable_objects_count()
    local count = 0
    for i=1,#object_list do
        if object_list[i].w > 1.0 then
            count = count + 1
        end
    end
    return count
end

--/---------------------------------------------------------------------/
function get_3d_pos()
    print(" Getting 3D position of " .. #object_list .. " objects")
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("get")
    cmd:addString("s2c")
    for i=1,#object_list do
        print("Object " .. i .." at 2D " .. object_list[i].u .. "," .. object_list[i].v  )
        local obj = cmd:addList()
        obj:addDouble(object_list[i].u)
        obj:addDouble(object_list[i].v)
    end
    are_get:write(cmd, rep)
    print("rep = " .. rep:toString())

    for i=0,rep:size()-1 do
        bt = rep:get(i):asList()  -- read bottle from reply
        -- write in i+1 because we are moving values from a C vector (0-indexed) to a LUA vector (1-indexed)
        if bt then
            object_list[i+1].x = bt:get(0):asDouble()
            object_list[i+1].y = bt:get(1):asDouble()
            object_list[i+1].z = bt:get(2):asDouble() + Z_OBJECT_OFFSET          --get position 4 cm above table (z+=0.04)
            print("Object " ..  i+1 .. " at 3D " .. object_list[i+1].x .. "," .. object_list[i+1].y .. "," .. object_list[i+1].z )
        else                     -- single object, does not come wrapped in bottle
            object_list[i+1].x = rep:get(0):asDouble()
            object_list[i+1].y = rep:get(1):asDouble()
            object_list[i+1].z = rep:get(2):asDouble() + Z_OBJECT_OFFSET          --get position 4 cm above table (z+=0.04)
            print("Object " .. i+1 .. " at 3D " .. object_list[i+1].x .. "," .. object_list[i+1].y .. "," .. object_list[i+1].z )
            return true
        end
    end
    return true
end


--/---------------------------------------------------------------------/
function update_object_list()
     -- returns false when no objects or no stable objects are received.
     -- Otherwise updates the objects'struct with the latest info.

    local t_now = yarp.Time_now()
    local blobs = blobs_port:read(false)
    if blobs ~= nil and blobs:size() >= 0 then      -- blobs received        
        leaky_integrate(object_list, blobs, t_now)  -- stabilize objects
        forget_expired_objects(object_list)

        --update_zone()

        return true
    else
      
        return false
    end
end


--/---------------------------------------------------------------------/
function get_object_zone(object)

    if object.y > MAX_Y or object.y < MIN_Y or object.x> MAX_X or object.x < MIN_X then
        return "OUT"
    end

    if object.y > CENTER_Y then
        if object.x > CENTER_X then
            return "BOTTOMRIGHT"
        end
        if object.x < CENTER_X then
            return "UPRIGHT"
        end
    else
        if object.x > CENTER_X then
            return "BOTTOMLEFT"
        end
         if object.x < CENTER_X then
            return "UPLEFT"
        end
    end
end


--/---------------------------------------------------------------------/
function update_zone()
    for i=1,#object_list do
        local obj = object_list[i]
        local zone = get_object_zone(obj)
        object_list[i].zone = zone
    end
    return true
end

function objects_in_workspace()
    for i=1,#object_list do
        local obj = object_list[i]
        if obj.zone ~= "OUT" then
            return true
        end
    end
    return false
end

function confirm_empty_table()
    -- If there are no blobs within the working area, and robot not busy, table is clean
    -- waits for 4 seconds before considering that the table is clean
    timer = yarp.Time_now() - empty_table_counter
    if timer > 5 then       
        if tableClean == false then
            speak("The table is now clean, hurray!")
            print("The table is now clean, hurray!")
            tableClean = true
        end
        if holdingTool == true then
            -- ask ARE to drop tool
            drop_tool()
            holdingTool = false
        end
        empty_table_counter = yarp.Time_now();
    end
end


----------------------------------
--        ASSIGN TASKS          --
----------------------------------

--/---------------------------------------------------------------------/
function select_object(objects)

    -- Prioritize objects according to their location
    for i, zone_search in ipairs(ZONES_LIST) do
        print("Looking for objects in zone " .. zone_search)

        for j, obj in ipairs(objects) do
            if obj.zone == zone_search then
                print("Target object in zone " .. zone_search .. " with coords" .. obj.x .. obj.y .. obj.z)
                return obj
            end
        end
    end

    print("No stable objects found on table!")
    return nil
end


--/---------------------------------------------------------------------/
function select_action(obj)

    local zone = obj.zone
    local act = "not_affordable"

    if zone == "OUT" then
        speak("Object out of reach!")
        print("Objects out of limits!!")
        return "not_affordable"
    end

    -- Reachable by hand (no tool required)
    if zone == "BOTTOMLEFT" then
        speak("Object reachable!")
        print("Objects reachable!!")
        return  "take_hand"
    end

    if zone == "BOTTOMRIGHT" then
        speak("Object bottomright!")
        print("Object bottomright!!")
        return "drag_left_hand"
    end

    -- Rachable only by tool (need to check tool Affs)

    -- Read tool affordances from tool-incorporator
    local aff_reply = get_tool_affordance()
    if aff_reply == nil then
        print("no reply from affCollector.")
        speak("affCollector does not respond")
        return "not_affordable"
    end
    print("Current affordances are:" .. aff_reply:toString())

    print("aff_reply:toString()= " .. aff_reply:toString() )
    print("aff_reply:get(0):asString()= " .. aff_reply:get(0):asString() )
    print("aff_reply:get(0):asList():get(0):asString()= " .. aff_reply:get(0):asList():get(0):asString() )

    if aff_reply:toString() == "(no_aff)" then
        print(aff_reply:toString())
        -- speak("I can not do anything with this tool")
        return  "not_affordable"
    end

    tool_pose = aff_reply:get(0):asList():get(0):asString()
    print("I got the tool-pose " .. tool_pose)

    print("aff_reply:get(0):asList():get(1):asString()= " .. aff_reply:get(0):asList():get(1):asDict():toString())      

    tool_affs = aff_reply:get(0):asList():get(1):asDict()
    print("With Affordances " .. tool_affs:toString())

    if zone == "UPLEFT" then
        if tool_affs:check("drag_down_right") == true then
            aff_prob = tool_affs:find("drag_down_right"):asDouble()
            if (aff_prob > 0.7) then
                speak("I will drag down right")
                return "drag_down_right"
            end
        end
    end

    if zone == "UPRIGHT" then
        if tool_affs:check("drag_down") == true then
            aff_prob = tool_affs:find("drag_down"):asDouble()
            if (aff_prob > 0.7) then
                speak("I will drag down")
                return "drag_down"
            end
        end
        speak("I can't drag down")
        if tool_affs:check("drag_left") == true then
            aff_prob = tool_affs:find("drag_left"):asDouble()
            if (aff_prob > 0.7) then
                speak("I will drag left")
                return "drag_left"
            end
        end
    end

    speak("I can not do anything useful with this tool")
    return "not_affordable"
end


--/---------------------------------------------------------------------/
function select_task(obj)

    local zone = obj.zone

    if zone == "BOTTOMLEFT" then
        return  "take_hand"
    end
    if zone == "BOTTOMRIGHT" then
        return "drag_left_hand"
    end
    if zone == "UPLEFT" then
        return "drag_down_right"
    end
    if zone == "UPRIGHT" then
        return "drag_down"
    end

    if zone == "OUT" then
        speak("Object out of reach!")
        print("Objects out of limits!!")
        return nil
    end

    speak("No task for this object")
    return nil
end



--/---------------------------------------------------------------------/

function get_tool_affordance()
    -- Call affCollector
    print("Checking tool affordances ")
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("getAffs")
    affcollect_rpc:write(cmd, rep)
    print(rep:toString())

    return rep
end

--/---------------------------------------------------------------------/
function get_object_in_zone(object_list, ZONE_X, ZONE_Y)
    closest_id = nil
    for i=1,#object_list do
        if object_list[i].w > 1.0 and
           object_list[i].x <= ZONE_X.max and
           object_list[i].x >= ZONE_X.min and
           object_list[i].y <= ZONE_Y.max and
           object_list[i].y >= ZONE_Y.min then
            if closest_id == nil or object_list[closest_id].x < object_list[i].x then
                closest_id = i
            end
        end
    end
    if closest_id == nil then return nil end
    return object_list[closest_id]
end


--/---------------------------------------------------------------------/
function update_tasks(object_list)
    for i=1,#object_list do
        local obj = object_list[i]
        --local zone = get_object_zone(obj)
        local task = select_task(obj)
        object_list[i].task = task
    end
    return true
end

----------------------------------
--        ROBOT COMMANDS       --
----------------------------------
function check_left_arm_busy()
    -- check the status the left arm
    --print("Checking if left arm is busy")
    local status = get_are_status()
    local leftarm_idle
    local lefthand_holding
    if status:find("left_arm"):asString() == "idle" then
        leftarm_idle = true
    else
        leftarm_idle = false
    end

    status = get_are_holding()
    if status:toString() == "[ack]" then
        lefthand_holding = true
    else
        lefthand_holding = false
    end

    -- do not do any other action if left arm is busy
    if not leftarm_idle or lefthand_holding then
        print("Left hand or arm is busy. Ignoring objects on the table!")
        --print("Status:", leftarm_idle, lefthand_holding, not leftarm_idle or lefthand_holding)
        return true
    end

    -- if hand idle and hand empty, return false -> not busy
    return false

end


--/---------------------------------------------------------------------/
function get_are_status()
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("get")
    cmd:addString("status")
    are_rpc:write(cmd, rep)
    return rep
end

function get_are_holding()
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("get")
    cmd:addString("holding")
    are_get:write(cmd, rep)
    return rep
end

function reset_wholebody()
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addInt(0)
    wholebody_rpc:write(cmd, rep)
end

--/---------------------------------------------------------------------/
function drop_tool()

    speak("Dropping the tool")

    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    rep:clear()
    cmd:addString("drop")
    cmd:addString("over")
    target = cmd:addList()
    target:addDouble(-0.15)
    target:addDouble(0.35)
    target:addDouble(0.0)
    cmd:addString("right")
    are_cmd:write(cmd, rep)

    cmd:clear()
    rep:clear()
    cmd:addString("cleartool")
    toolinc_rpc:write(cmd, rep)
    
    -- send same command 'cleartool' to affCollector.
    affcollect_rpc:write(cmd, rep)

    speak("I'm done")
end

----------------------------------
--    SELECT AND GET TOOL       --
----------------------------------

--/---------------------------------------------------------------------/
function select_tool(task)
    -- get index of desired task
    --local act_i = find_key(TOOL_ACTIONS, task)
    --print("task ".. task .. " has index ".. act_i)

    -- Call affCollector to return the best tool's label for a given task
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("selectTool")
    cmd:addString(task)      -- Transform to C++ 0-indexing
    affcollect_rpc:write(cmd, rep)

    local tool = rep:get(0):asString()
    print("Tool selected is " .. tool)

    return tool
end


function set_act_labels(TOOL_ACTIONS)
    -- Call affCollector to return the best tool's label for a given task
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("setactlabels")
    local act_labels = cmd:addList()
    for i, action in  ipairs(TOOL_ACTIONS) do
        act_labels:addString(action)
    end
    affcollect_rpc:write(cmd, rep)
    return true
end


function get_act_labels()
    -- Call affCollector to return the best tool's label for a given task
    local ACTION_LIST = {}
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("getactlabels")

    print("command sent to affCollector: " .. cmd:toString())
    affcollect_rpc:write(cmd, rep)

    print("Bottle read " .. rep:toString())

    for i=0,rep:size()-1 do
        act_label = rep:get(i):asString()  -- read strings from reply
        table.insert(ACTION_LIST, i+1, act_label)
    end
    print ("actions read: ")
    for key,value in pairs(ACTION_LIST) do print(key,value) end

    return ACTION_LIST
end

--/---------------------------------------------------------------------/
function set_tool_label(tool_pose)
    --print("Sending label to affCollector")
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("setlabel")
    cmd:addString(tool_pose)
    --print("Sending: ".. cmd:toString())
    affcollect_rpc:write(cmd, rep)
    --print("Received:".. rep:toString())
    print("label ", tool_pose, "set in affCollector")
    return true
end


--/---------------------------------------------------------------------/
function ask_for_tool(tool_name)



    print("grasp the tool")
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("graspTool")
    if tool_name ~= nil then
        speak("Give me the " .. tool_name)
        cmd:addString(tool_name)
    end
    tmanager_rpc:write(cmd, rep)

    local tool_loaded = rep:get(0):asString()

    if tool_loaded == "not_loaded" then  return "invalid"   end

    print("find the tool pose")
    cmd:clear()
    rep:clear()
    cmd:addString("findPose")
    tmanager_rpc:write(cmd, rep)

    local reply = rep:get(0):asString()
    if reply ~= "ok" then
        speak("I could not find the pose" )
        print("I could not find the pose" )
        return "invalid"
    end

    print("getting orientation")
    cmd:clear()
    rep:clear()
    cmd:addString("getOri")
    toolinc_rpc:write(cmd, rep)
    print("GetOri reply".. rep:toString())

    local deg
    if rep:get(1):asDouble() then
        deg = rep:get(1):asDouble()
        print("Deg:".. deg)
    else
        print("Orientation couldn't be retreived" )
        return "invalid"
    end

    local pose = deg2ori(deg)
    if pose == "out" then
        print("Pose out of limits" )
        return "invalid"
    end

    tool_pose = tool_loaded .. "_" .. pose

    print("Deg: ".. deg ..  " -> Pose", pose)
    print("Tool".. tool_loaded .. " oriented ".. pose.. " -> tool-pose " .. tool_pose)

    return tool_pose
end

--/---------------------------------------------------------------------/
function deg2ori(deg)
    if (deg > 45.0) and (deg < 135.0) then        -- oriented left
        ori = "left"
        speak(" oriented to the left")
    elseif ((deg < 45.0) and (deg > -45.0)) then  -- oriented front
        ori = "frnt";
        speak(" oriented to the front")
    elseif (deg > -135.0) and (deg < -45.0) then  -- oriented right
        ori = "rght";
        speak(" oriented to the right")
    else
        return "out";
    end
    return ori
end


----------------------------------
--       MOTOR FUNCTIONS        --
----------------------------------
function clear_tool()
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:clear()
    cmd:addString("cleartool")
    toolinc_rpc:write(cmd, rep)

    cmd:clear()
    cmd:addString("cleartool")
    affcollect_rpc:write(cmd, rep)

end


function go_home(hands)
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:clear()
    cmd:addString("goHome")
    cmd:addInt(hands)
    tmanager_rpc:write(cmd, rep)
end

function perform_action(action, object)

    -- Hand actions
    if action == "take_hand" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("take")
        pos = cmd:addList()
        pos:addDouble(object.x + X_GRASP_OFFSET)
        pos:addDouble(object.y + Y_GRASP_OFFSET)
        pos:addDouble(object.z + Z_GRASP_OFFSET)
        cmd:addString("left")
        are_cmd:write(cmd, rep)
        print(cmd:toString())
        while check_left_arm_busy() do
            -- Just wait until arm is not busy 
            yarp.Time_delay(0.2)                                   
        end
        -- Return control once left arm is not busy anymore
        return true
    end
    if action == "drag_left_hand" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x - 0.05)
        cmd:addDouble(object.y + 0.07)
        cmd:addDouble(object.z + 0.0)
        cmd:addDouble(180)
        cmd:addDouble(math.abs(object.y - (REACHABLE_ZONE_Y.max - 0.10)))
        cmd:addDouble(0.0)              -- remove tool tilt
        cmd:addInt(0)                   -- select no tool
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end

    -- Tool actions
    if action == "drag_down" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x - 0.08)
        cmd:addDouble(object.y)
        cmd:addDouble(object.z - 0.02)
        cmd:addDouble(270)
        cmd:addDouble(math.abs(object.x -(CENTER_X + 0.07)))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    if action == "drag_left" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x - 0.05)
        cmd:addDouble(object.y + 0.1)
        cmd:addDouble(object.z - 0.01)
        cmd:addDouble(180)
        cmd:addDouble(math.abs(object.y - (CENTER_Y - 0.10)))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    if action == "drag_right" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x - 0.06)
        cmd:addDouble(object.y - 0.02)
        cmd:addDouble(object.z - 0.01)
        cmd:addDouble(0)
        cmd:addDouble(math.abs(object.y - (CENTER_Y + 0.10)))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    if action == "drag_down_right" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x - 0.06)
        cmd:addDouble(object.y - 0.08)
        cmd:addDouble(object.z - 0.02)
        cmd:addDouble(315)
        local a = math.abs(object.y - (CENTER_Y + 0.10))
        local b = math.abs(object.x - (CENTER_X + 0.05))
        cmd:addDouble(math.sqrt(a*a + b*b))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    if action == "drag_up" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x + 0.04)
        cmd:addDouble(object.y)
        cmd:addDouble(object.z)
        cmd:addDouble(90)
        cmd:addDouble(math.abs(object.x -(CENTER_X - 0.07)))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    if action == "drag_up_left" then
        local cmd = yarp.Bottle()
        local rep = yarp.Bottle()
        cmd:addString("drag3D")
        cmd:addDouble(object.x + 0.03)
        cmd:addDouble(object.y + 0.02)
        cmd:addDouble(object.z)
        cmd:addDouble(135)
        local a = math.abs(object.y - (CENTER_Y - 0.07))
        local b = math.abs(object.x - (CENTER_X - 0.07))
        cmd:addDouble(math.sqrt(a*a + b*b))
        print(cmd:toString())
        tmanager_rpc:write(cmd, rep)
        return true
    end
    -- no action was done
    return false
end



----------------------------------
--   COMPUTE AND SAVE EFFECT    --
----------------------------------
function comp_effect(obj, obj_prev, bin_flag)
    local eff
    --if binF == true, effect is binary (success/fail), where success is if the object changed its ZONE
    if bin_flag == true then
        local zone = get_object_zone(obj)
        local zone_prev = get_object_zone(obj_prev)
        if zone == zone_prev then
            eff = 0                 -- same zone: no success
        else
            eff = 1                 -- different zone: success
        end
    else

    --if binF == false, effect is euclidean, measured as the 2D distance displaced in plane XY
        eff = math.sqrt((obj.x-obj_prev.x)*(obj.x-obj_prev.x) + (obj.y-obj_prev.y)*(obj.y-obj_prev.y))
    end

    return eff
end

function save_effect(act_i, eff)
    local bot = yarp.Bottle()
    bot:clear()
    bot:addInt(act_i)
    bot:addDouble(eff)

    print("Sending: acteff_bot ".. bot:toString())
    acteff_port:write(bot)
end

function save_affordances()
    --print("Sending label to affCollector")
    local cmd = yarp.Bottle()
    local rep = yarp.Bottle()
    cmd:addString("savetofile")
    affcollect_rpc:write(cmd, rep)
    print("Affordance knowledge saved to file")
    return true
end




----------------------------------
-- functions SPEECH             --
----------------------------------

function SM_RGM_Expand(port, vocab, word)
    local wb = yarp.Bottle()
    local reply = yarp.Bottle()
    wb:clear()
    wb:addString("RGM")
    wb:addString("vocabulory")
    wb:addString("add")
    wb:addString(vocab)
    wb:addString(word)
    port:write(wb)
    --port:write(wb,reply)
    return "OK" --reply:get(1):asString()
end

function SM_Expand_asyncrecog(port, gram)
    local wb = yarp.Bottle()
    local reply = yarp.Bottle()
    wb:clear()
    wb:addString("asyncrecog")
    wb:addString("addGrammar")
    wb:addString(gram)
    port:write(wb,reply)
end

function SM_Reco_Grammar(port, gram)
    local wb = yarp.Bottle()
    local reply = yarp.Bottle()
    wb:clear()
    wb:addString("recog")
    wb:addString("grammarSimple")
    wb:addString(gram)
    port:write(wb,reply)
    return reply
end

function SM_RGM_Expand_Auto(port, vocab)
    local wb = yarp.Bottle()
    local reply = yarp.Bottle()
    wb:clear()
    wb:addString("RGM")
    wb:addString("vocabulory")
    wb:addString("addAuto")
    wb:addString(vocab)
    port:write(wb,reply)
    return reply:get(1):asString()
end


function speak(msg)
   local wb = ispeak_port:prepare()
   wb:clear()
   wb:addString(msg)
   ispeak_port:write()
   yarp.Time_delay(1.0)

end

----------------------------------
--          HELPERS             --
----------------------------------
function find_key( list, value )
  for k,v in pairs(list) do
    if v==value then return k end
  end
  return nil
end

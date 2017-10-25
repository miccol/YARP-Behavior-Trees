 print("State = ".. state)
print("in substate OBSERVE, checking objects on the table!")
empty_table_counter = yarp.Time_now()


while true do
  while true do

     -- Read blobs and update objects in memory and associate zones 
      if update_object_list() == false then 
          --print("No blobs received")                           
          confirm_empty_table()                                                                     
          break
      end
      
      -- check if received blobs are stable
      if get_stable_objects_count() == 0  then
          confirm_empty_table()
          --print("Blobs received not stable")                                                
          break
      end

      print("Received " .. #object_list .. " stable blobs")  

      -- slow down the commands to the action rendering port
      if (yarp.Time_now() - t0) < 1.0 then
         break
      else
         t0 = yarp.Time_now()
         reset_wholebody()
      end

      -- get the 3D position
      get_3d_pos()
      update_zone()

      print("Received " .. #object_list .. " blobs")
      for i=1,#object_list do
          local obj = object_list[i]
          print("Object " .. i )
          print("-2D coords (" .. obj.u .. "," .. obj.v  .. ")" )
          print("-3D coords (" .. obj.x .. ", " .. obj.y .. ", " .. obj.z .. "), Zone: "   .. obj.zone)
      end
    
      -- Check if there is any blob inside the workspace
      if objects_in_workspace() == false then                  
         if tooFarSaid == false then
             speak("Objects are too far!")                           
             tooFarSaid = true
         end
         print("Objects are too far!!!")
         confirm_empty_table()                                                
         break
      end


     -- if arm is busy, ignore blobs.
     if check_left_arm_busy() == true then
         break
     end

     -- receiving blobs in workspace on idle robot: 
     empty_table_counter = yarp.Time_now()
     tableClean = false



     -- decide which object to target and the corresponding action
     target_object = select_object(object_list)
     if target_object == nil then
         break
     end



     speak("Targeting object")
     print("Targeting object at = ".. target_object.x .. target_object.y .. target_object.z)

     tooFarSaid = false
     state = "select_action"      -- select action given affordance
     return true

     go_home(0)


  end
--rfsm.yield(true)
end



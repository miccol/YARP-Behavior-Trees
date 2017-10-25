                 print("State = "..state)

                 if TOOL_SELECTION_FLAG == true then
                     -- select_tool
                     task = select_task(target_object)
                     if task ~= nil then

                         tool_selected = select_tool(task)
                         print("Tool Selected:".. tool_selected)

                         if tool_selected  ~= "no_tool" then
                             tool_given = ask_for_tool(tool_selected)   -- Grasps and recognizes tool
                         else
                             print("Could not select a proper tool")
                             tool_given = "invalid"
                         end
                     else
                         tool_given = "invalid"
                     end

                 else
                     -- ask tool
                     tool_given = ask_for_tool()
                 end

                 print("Tool given: " .. tool_given)

                 if tool_given ~= "invalid" then
                     holdingTool= true
                     set_tool_label(tool_given)    --  Set tool received as active label on affCollector
                 else
                     print("Could not get the tool, lets try again")
                     -- state = "select_tool"
                     -- rfsm.send_events(fsm,'e_gettool')
                 end
                 state = "observe"
                 return false
                 go_home(0)
is_action_done = false

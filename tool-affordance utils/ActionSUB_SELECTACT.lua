               speak("Selecting action")
               print("State = " .. state)

               action = select_action(target_object)

               -- task is NOT doable with tool present (if at all)
               if action == "not_affordable" then

                   -- Not holding any tool yet
                   if holdingTool == false then
                       print("I need a tool")
                       speak("I need a tool.")
                   else -- Already holding a tool
                       print("Give me another one")
                       speak("Give me another one")
                   end

                   state = "get_tool"
                   return false

               else
                   -- task is doable
                   state = "do_action"
                   speak("I can do action ", action)
                   return true
               end

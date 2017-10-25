print("State = "..state)
print("Performing action ", action)
local actOK = perform_action(action, target_object)
if actOK then
  print("Action Performed: ", action)
  --state = "comp_effect"
  state = "observe"
 else
  print("Action ", action, "could not be executed")
end
return true

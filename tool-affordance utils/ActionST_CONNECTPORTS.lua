print("Connecting ports ... ")
-- Connect
if not yarp.NetworkBase_connect("/lbpExtract/blobs:o", blobs_port:getName()) then print (blobs_port:getName() .. " NOT connected")  else print (blobs_port:getName() .. " connected")  end
if not yarp.NetworkBase_connect(acteff_port:getName(),"/affCollector/aff:i") then print (acteff_port:getName() .. " NOT connected")  else print (acteff_port:getName() .. " connected")  end


-- Connect to RPCs
-- To other APP modules  /toolIncorporator/rpc:i
if not yarp.NetworkBase_connect(toolinc_rpc:getName(),"/toolIncorporator/rpc:i") then print (toolinc_rpc:getName() .. " NOT connected")  else print (toolinc_rpc:getName() .. " connected")  end
if not yarp.NetworkBase_connect(tmanager_rpc:getName(),"/tool3DManager/rpc:i") then print (tmanager_rpc:getName() .. " NOT connected")  else print (tmanager_rpc:getName() .. " connected")  end
if not yarp.NetworkBase_connect(affcollect_rpc:getName(),"/affCollector/rpc:i") then print (affcollect_rpc:getName() .. " NOT connected") else print (affcollect_rpc:getName() .. " connected") end

-- AREs
if not yarp.NetworkBase_connect(are_cmd:getName(),"/actionsRenderingEngine/cmd:io") then print (are_cmd:getName() .. " NOT connected")  else print (are_cmd:getName() .. " connected")  end
if not yarp.NetworkBase_connect(are_rpc:getName(),"/actionsRenderingEngine/rpc") then print (are_rpc:getName() .. " NOT connected")  else print (are_rpc:getName() .. " connected")  end
if not yarp.NetworkBase_connect(are_get:getName(),"/actionsRenderingEngine/get:io") then print (are_get:getName() .. " NOT connected")  else print (are_get:getName() .. " connected")  end

-- Wholebody for reset
if not yarp.NetworkBase_connect(wholebody_rpc:getName(),"/wholeBodyDynamics/rpc:i") then print (wholebody_rpc:getName() .. " NOT connected")  else print (wholebody_rpc:getName() .. " connected")  end

-- Speech
if not yarp.NetworkBase_connect(speechRecog_port:getName(),"/speechRecognizer/rpc") then print (speechRecog_port:getName() .. " NOT connected") else print (speechRecog_port:getName() .. " connected") end
if not yarp.NetworkBase_connect(ispeak_port:getName(),"/iSpeak") then print (ispeak_port:getName() .. " NOT connected")  else print (ispeak_port:getName() .. " connected")  end
return true

print("Opening ports ... ")
-- Open ports
ret = blobs_port:open("/xperience_sm/blobs:i")
ret = ret and acteff_port:open("/xperience_sm/act_eff:o")
ret = ret and ispeak_port:open("/xperience_sm/ispeak:o")
ret = ret and speechRecog_port:open("/xperience_sm/speechRecog")
if ret == false then
	print("\nERROR OPENING PORTS\n")
	return true
end

-- rpc
ret = are_get:open("/xperience_sm/are_get:rpc")
ret = ret and are_cmd:open("/xperience_sm/are_cmd:rpc")
ret = ret and are_rpc:open("/xperience_sm/are_rpc:rpc")
ret = ret and wholebody_rpc:open("/xperience_sm/wb:rpc")

ret = ret and toolinc_rpc:open("/xperience_sm/toolinc:rpc")
ret = ret and tmanager_rpc:open("/xperience_sm/t3dm:rpc")
ret = ret and affcollect_rpc:open("/xperience_sm/affcol:rpc")
if ret == false then
	print("\nERROR OPENING RPC PORTS\n")
	return true
end
return true

print("Module running ... ")
t0 = yarp.Time_now()
math.randomseed( os.time() )

print("everything is fine, going home!")
go_home(1)
clear_tool()

speak("Ready")
print("Ready")
return true

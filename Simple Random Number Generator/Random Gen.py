import random
ProgRun = True
while ProgRun == True:
	Running = raw_input("Generate a random number (Y or N)? ")
	if Running == "Y" or Running == "y":
		lowerbound = int(raw_input("Enter lower bound: "))
		upperbound = int(raw_input("Enter upper bound: "))
		print(random.randint(lowerbound,upperbound))
		ProgRun = True
	elif Running == "N" or Running == "n":
		ProgRun = False
	else:
		Running = input("Invalid selection. Hit Enter to continue: ")
		ProgRun = True
print("Hit enter to exit.")	

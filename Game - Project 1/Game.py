def playerinfosetup():
	filename = input("Enter player name: ")+'.txt'
	if filename == "upupdowndownleftrightleftrightba.txt":
		filename = "konami.txt"
		return filename
	else:
		fowrite = open(filename, 'w')
		fowrite.write("3\n5\n2\n7\nchallenge1.txt")
		fowrite.close()
		return filename

def playerinfoopen():
	filename = input("Enter player name: ")+'.txt'
	if filename == "upupdowndownleftrightleftrightba.txt":
		filename = "konami.txt"
	return filename
	
def playerselect():
	playerselection = True
	while playerselection == True:
		fileopener = input("(N)ew game or (C)ontinue playing? ")
		if fileopener == "N" or fileopener == "n":
			filename = playerinfosetup()
			playerselection = False
		elif fileopener == "C" or fileopener == "c":
			filename = playerinfoopen()
			playerselection = False
		else:
			print("Invalid answer. Hit enter to continue: ")
			playerselection = True
	return filename

def challenge1(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "H" or postquestion == "h":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge2.txt")
			else:
				fileobject.write("5\n5\n4\n8\nchallenge2.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "G" or postquestion == "g":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge3.txt")
			else:
				fileobject.write("5\n5\n4\n8\nchallenge3.txt")
			return True
		else:
			print("Invalid answer")

def challenge2(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "P" or postquestion == "p":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge4.txt")
			else:
				fileobject.write("10\n10\n10\n10\nchallenge4.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "G" or postquestion == "g":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge5.txt")
			else:
				fileobject.write("10\n10\n10\n10\nchallenge5.txt")
			return True
		else:
			print("Invalid answer")

def challenge3(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "G" or postquestion == "g":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge5.txt")
			else:
				fileobject.write("10\n10\n10\n10\nchallenge5.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "I" or postquestion == "i":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge6.txt")
			else:
				fileobject.write("10\n10\n10\n10\nchallenge6.txt")
			return True
		else:
			print("Invalid answer")

def challenge4(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "F" or postquestion == "f":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge7.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge7.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "C" or postquestion == "c":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge8.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge8.txt")
			return True
		else:
			print("Invalid answer")

def challenge5(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "W" or postquestion == "w":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge7.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge7.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "E" or postquestion == "e":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge8.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge8.txt")
			return True
		else:
			print("Invalid answer")

def challenge6(challengeposttext, filename):
	challenge = True
	while challenge == True:
		postquestion = input(challengeposttext)
		if postquestion == "F" or postquestion == "f":
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge7.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge7.txt")
			challenge = False
			return True
		elif postquestion == "Q" or postquestion == "q":
			challenge = False
			return False
		elif postquestion == "C" or postquestion == "c":	
			fileobject = open(filename, "r+")
			if filename == "konami.txt":
				fileobject.write("200\n200\n200\n200\nchallenge8.txt")
			else:
				fileobject.write("15\n15\n15\n15\nchallenge8.txt")
			return True
		else:
			print("Invalid answer")

def challenge7(challengeposttext, filename):
	print(challengeposttext)
	
def challenge8(challengeposttext, filename):
	print(challengeposttext)

def main():
	gamerun = True
	while gamerun == True:
		gamestart = input("Instructions: To (P)lay the game, enter the letter in the parentheses to select your adventure.  You can (Q)uit at any time by entering q or Q whenever the game asks for a single letter input.  Enter P to (P)lay or Q to (Q)uit: ")
		if gamestart == "q" or gamestart == "Q":
			gamerun = False
		elif gamestart == "p" or gamestart == "P":
			filename = playerselect()
			Challenge = True
			while Challenge == True:
				
				fileobject = open(filename, "r+")
				playerattack = float(fileobject.readline())
				playermagic = float(fileobject.readline())
				playerarmor = float(fileobject.readline())
				playerhealth = float(fileobject.readline())
				challenge = fileobject.readline()
				realchallenge = challenge.replace("\n", "")
				challengeobject = open(realchallenge, "r+")
				challengeattack = float(challengeobject.readline())
				challengemagic = float(challengeobject.readline())
				challengearmor = float(challengeobject.readline())
				challengehealth = float(challengeobject.readline())
				challengepretext = challengeobject.readline()
				challengelooptext = challengeobject.readline()
				challengeattackdamage = challengeobject.readline()
				challengemagicdamage = challengeobject.readline()
				challengeposttext = challengeobject.readline()
				print(challengepretext)
				
				while challengehealth > 0:
					pretextanswer = input(challengelooptext)
					if pretextanswer == "a" or pretextanswer == "A":
						print(challengeattackdamage)
						challengehealth = challengehealth+challengearmor-playerattack
					elif pretextanswer == "m" or pretextanswer == "M":
						print(challengemagicdamage)
						challengehealth = challengehealth+challengearmor-playermagic
					elif pretextanswer == "q" or pretextanswer == "Q":
						challengehealth = 0
						Challenge = False
					else:
						print("Invalid answer.")
				if pretextanswer == "Q" or pretextanswer == "q":
					gamerun == False
				else:	
					if realchallenge == "challenge1.txt":
						challenge1(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge2.txt":
						challenge2(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge3.txt":
						challenge3(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge4.txt":
						challenge4(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge5.txt":
						challenge5(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge6.txt":
						challenge6(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
					elif realchallenge == "challenge7.txt":
						challenge7(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
						Challenge = False
					elif realchallenge == "challenge8.txt":
						challenge8(challengeposttext, filename)
						fileobject.close()
						challengeobject.close()
						Challenge = False
					else:
						Challenge = False

		gamerun = False
	print("Hit enter to exit.")
	
main()
	

"""
*********************
** SaiKumar Immadi **
****** 1501058 ******
*********************
"""
"""
This program implements simplex method.
The two articles below were followed while implementing the program.
https://www.zweigmedia.com/RealWorld/tutorialsf4/framesSimplex.html
https://www.zweigmedia.com/RealWorld/tutorialsf4/framesSimplex2.html
"""

# Uses Python 2
# python Init.py
# or
# python Init.py < inputs/input1

# Function to return GCD of two numbers
def gcd(a,b):
	if a == b:
		return a
	if a > b:
		return gcd(a-b, b)
	return gcd(a, b-a)
 
# Function to return LCM of two numbers
def lcm(a,b):
	return (a*b) / gcd(a,b)

# another lcm function if any recursion error occurs
# def lcm(x,y):
# 	if x > y:
#    		greater = x
#    	else:
# 		greater = y
#    	while True:
# 		# print x,y
# 	  	if (greater % x == 0) and (greater % y == 0):
# 			lcm = greater
# 			break
# 	   	greater += 1
#    	return lcm
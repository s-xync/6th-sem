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

# Function for row operations
def listDifference(list1,list2,a1,a2):
	"""
	inputs : list1,list2,a1,a2
	returns : outputList 
	outputList = a1*list1-a2*list2
	"""
	assert len(list1)==len(list2)
	outputList=[]
	for i in range(0,len(list1)):
		outputList.append(a1*list1[i] - a2*list2[i])
	return outputList
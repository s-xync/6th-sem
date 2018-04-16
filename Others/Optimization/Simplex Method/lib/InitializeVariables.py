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

# to initilize matrix and basic variables
def initialize(matrix,basic_vars,num_var,num_const):
	# Zero Matrix of size (num_const+1 x num_var+num_const+1+1)
	# starts creating a zeros matrix
	for i in range(0,num_const+1):
		tempList=[]
		for j in range(0,num_var+num_const+1+1):
			tempList.append(0)
		matrix.append(tempList)
	# completes creating zeros matrix

	# adds those column numbers(0 indexed) who are basic variables right now
	for i in range(0,num_const):
		basic_vars.append(i+num_var)
	return (matrix,basic_vars)
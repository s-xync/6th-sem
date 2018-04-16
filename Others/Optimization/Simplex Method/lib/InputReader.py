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

# to take inputs from user
def readFromUser(matrix,num_var,num_const,choice):
	# starts taking inputs for constraints
	print "***please keep RHS of constraints positive***"
	for i in range(0,num_const):
		for j in range(0,num_var):
			matrix[i][j]=input("constraint "+str(i+1)+" variable "+str(j+1)+" : ")
			assert isinstance(matrix[i][j],int)

		print "Greater Than --> -1\nLess Than --> 1"
		matrix[i][num_var+i]=input("constraint "+str(i+1)+" GT or LT : ")
		assert isinstance(matrix[i][num_var+i],int)
		assert matrix[i][num_var+i]==-1 or matrix[i][num_var+i]==1

		matrix[i][num_var+num_const+1]=input("constraint "+str(i+1)+" RHS : ")
		assert isinstance(matrix[i][num_var+num_const+1],int)
		assert matrix[i][num_var+num_const+1]>=0
	# completes taking inputs for constraints
	# starts taking inputs for objective function
	for i in range(0,num_var):
		matrix[num_const][i]=choice*input("Objective Function Variable "+str(i+1)+" : ")
		assert isinstance(matrix[num_const][i],int)
	
	matrix[num_const][num_const+num_var]=1
	# completes taking inputs for objective function

	return matrix
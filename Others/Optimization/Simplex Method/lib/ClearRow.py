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

# Function for clearing on pivot column
import RowOperation
import LCM
def pivot_clearing(matrix,pivot_row,pivot_column,num_const):
	# pivot starts clearing other elements in the pivot column
	for i in range(0,num_const+1):
		if i!=pivot_row and matrix[i][pivot_column]!=0:
			# also if it is already cleared, don't clear it again
			# cannot send negative values to lcm function
			m1=1
			m2=1
			if matrix[pivot_row][pivot_column]<0:
				m1=-1
			if matrix[i][pivot_column]<0:
				m2=-1
			lcm_value=LCM.lcm(m1*matrix[pivot_row][pivot_column],m2*matrix[i][pivot_column])
			lcm_value=lcm_value*m1*m2
			matrix[i]=RowOperation.listDifference(matrix[i],matrix[pivot_row],lcm_value/matrix[i][pivot_column],lcm_value/matrix[pivot_row][pivot_column])
	# pivot completes clearing other elements in the pivot column
	return matrix

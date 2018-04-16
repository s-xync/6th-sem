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

import ClearRow

def phaseone(matrix,basic_vars,num_var,num_const):
	# to remove negative values to basic variables
	# Phase 1
	starFlag=True
	while starFlag:
		starFlag=False
		starRows=[]
		# deciding which rows to flag
		for basic_var in basic_vars:
			if matrix[basic_vars.index(basic_var)][basic_var]<0:
				starFlag=True
				starRows.append(basic_vars.index(basic_var))
		if not starFlag:
			# when all the flags are cleared, the loop will break
			break
		else:
			# starts calculating pivot column and then pivot row
			for starRow in starRows:
				if max(matrix[starRow][0:-1])>=0:
					pivot_column=matrix[starRow][0:-1].index(max(matrix[starRow][0:-1]))
					break
			# pivot column calculation
			ratio_dictionary={}
			for i in range(0,num_const):
				if matrix[i][pivot_column]>0:
					ratio_dictionary[i]=matrix[i][num_var+num_const+1]/matrix[i][pivot_column]
			
			min_ratio=min(ratio_dictionary.values())
			
			for key in ratio_dictionary.keys():
				if ratio_dictionary[key]==min_ratio:
					pivot_row=key
			# completes calculating pivot column and then pivot row
			# pops basic variable from basic_vars list positioned at pivot_row (0 indexed)
			basic_vars.pop(pivot_row)
			# inserts basic variable pivot_column to basic_vars list at pivot_row (0 indexed)
			basic_vars.insert(pivot_row,pivot_column)
			matrix=ClearRow.pivot_clearing(matrix,pivot_row,pivot_column,num_const)
			# if starFlag was active, it goes into while loop again
	return (matrix,basic_vars)


def normalPhase(matrix,basic_vars,num_var,num_const,flag):
	# normal phase
	while min(matrix[num_const][0:-1])<0:
		# starts calculating pivot column and then pivot row
		pivot_column=matrix[num_const][0:-1].index(min(matrix[num_const][0:-1]))
		# pivot column calculation
		ratio_dictionary={}
		for i in range(0,num_const):
			if matrix[i][pivot_column]>0:
				ratio_dictionary[i]=matrix[i][num_var+num_const+1]/matrix[i][pivot_column]
		
		# If dictionary is empty, it means that Unbounded Solution
		if len(ratio_dictionary)==0:
			flag=2
			return (matrix,basic_vars,flag)
		min_ratio=min(ratio_dictionary.values())
		
		for key in ratio_dictionary.keys():
			if ratio_dictionary[key]==min_ratio:
				pivot_row=key
		# completes calculating pivot column and then pivot row
		
		# pops basic variable from basic_vars list positioned at pivot_row (0 indexed)
		basic_vars.pop(pivot_row)
		# inserts basic variable pivot_column to basic_vars list at pivot_row (0 indexed)
		basic_vars.insert(pivot_row,pivot_column)

		# all the pivot column clearning operations will take place in the function
		matrix=ClearRow.pivot_clearing(matrix,pivot_row,pivot_column,num_const)
				
		# if any negative elements remain in matrix[num_const], goes for next iteration
	return (matrix,basic_vars,flag)

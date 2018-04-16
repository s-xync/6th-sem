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

# Main Function
import ClearRow
import Simplex
import InitializeVariables
import InputReader
def main():
	print "Max --> -1\nMin --> 1"
	# the choice can directly be multiplied with the objective function inputs 
	# to make it a standard maximisation problem always
	choice=input("Max or Min : ")
	assert isinstance(choice,int)
	assert choice==-1 or choice==1

	# num_var --> number of varibles
	num_var=input("How many variables : ")
	assert isinstance(num_var,int)
	assert num_var>1

	# num_const --> number of constraints
	num_const=input("How many constraints : ")
	assert isinstance(num_const,int)
	assert num_const>1

	matrix=[]
	basic_vars=[]
	# initialize matrix with zeroes and basic_vars list with slack and surplus variables
	matrix,basic_vars=InitializeVariables.initialize(matrix,basic_vars,num_var,num_const)
	# read from user and store them in the matrix
	matrix=InputReader.readFromUser(matrix,num_var,num_const,choice)

	flag=0
	# 0 --> unique solution
	# 1 --> alternative solution
	# 2 --> unbounded solution	# phase 1
	matrix,basic_vars=Simplex.phaseone(matrix,basic_vars,num_var,num_const)
	# normal phase
	matrix,basic_vars,flag=Simplex.normalPhase(matrix,basic_vars,num_var,num_const,flag)

	# results
	print "\n"
	print "*********************************************************"
	print "\n"
	if flag==0:
		print "we have a unique solution"
	elif flag==1:
		print "we have an alternative solution"
	elif flag==2:
		print "we have an unbounded solution"
		return 0
	
	print "The solution is",matrix[num_const][num_var+num_const+1]/matrix[num_const][num_var+num_const]
	print "\n"
	print "The final matrix is :"
	for i in range(0,num_const+1):
		print matrix[i]
	print "\n"
	print "The basic variables are",basic_vars,"(0 indexed)\n"
	for i in range(0,len(basic_vars)):
		print "The value of the",basic_vars[i],"variable is",matrix[i][num_var+num_const+1]/matrix[i][basic_vars[i]]

	for i in range(0,num_var+num_const): # no need to traverse on bottom right corner
		if i not in basic_vars and matrix[num_const][i]==0:
			flag=1

	return 0
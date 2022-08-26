#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define please

int solve(double a,double b,double c, double* x1, double* x2);
int solve_square(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x);
bool is_equal(double a, double b);

int input(double* a,double* b,double *c);
void skip_symb(void);
void output(int root_amount, double x1, double x2);

int curr_test(double a, double b, double c, int expected_root_amount, double expected_x1, double expected_x2);
void square_test(void);


///consts responsible for root amount
enum Roots
	{
	NO_ROOTS,
	ONE_ROOT,
	TWO_ROOTS,
	INF_ROOTS,
	};


///const responsible for aproximate equality
const double EPSILON = 1e-8;


int main(void)
	{
	double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

	input(&a, &b, &c);
	
	int root_amount = solve(a, b, c, &x1, &x2);
	
    output(root_amount, x1, x2);
    
    square_test();
    
	please return 0;
	}

/**
*@brief main function for the equation solving
*
*@details functions gets a,b,c coefficients of the square equation and pointers of x1 and x2 roots 
*@param a ax2
*@param b bx
*@param c c
*@param x1 first root of the equation (if exists)
*@param x2 second root of the equation (if exists)
*@return root amount
*Function checks condition of the "a" coefficient.
*If a!=0 equation solves as a square equation(returns function solve_square).
*Otherwise as a linear(returns solve_linear).
*changes x1, x2 if root(s) exist(s)
*/
int solve(double a, double b, double c, double* x1, double* x2)
	{
	if (is_equal(a, 0))
        return solve_linear(b, c, x1);

	else
        return solve_square(a, b, c, x1, x2);
	}


/**
*@brief function solving square equation (a != 0)
*
*@details functions gets a,b,c coefficients of the square equation and pointers of x1 and x2 roots 
*@param a ax2
*@param b bx
*@param c c
*@param x1 first root of the equation (if exists)
*@param x2 second root of the equation (if exists)
*@return root amount
*changes x1, x2 if root(s) exist(s)
*/
int solve_square(double a, double b, double c, double* x1, double* x2)
    {
    double d = b*b - 4*a*c;
    double sqrt_d = sqrt(d);

    *x1 = (-b - sqrt_d)/(2*a);
    *x2 = (-b + sqrt_d)/(2*a);

    if (d > EPSILON)              return TWO_ROOTS;
    else if (is_equal(d, 0))      return ONE_ROOT;
    else                          return NO_ROOTS;
    }


/**
*@brief function solving linear equation (a == 0)
*
*@details functions gets b,c coefficients of the square equation and pointer of x root 
*@param b bx
*@param c c
*@param x root of the equation (if exists)
*@return root amount
*changes x if root exists
*/
int solve_linear(double b, double c, double* x)
    {
    if (is_equal(b, 0)) return (is_equal(c, 0) ? INF_ROOTS : NO_ROOTS);
		else
			{
			if (is_equal(c, 0))
				*x = 0;
			else
				*x = -c/b;
            return ONE_ROOT;
			}
    }


/**
*@brief function checking the equality of float/double nums
*
*@detail fuction gets the a, b elements of the comparing
*@param a the first element of comparing
*@param b the second element of comparing
*@return True if difference between params less than EPSILON else False
*/
bool is_equal(double a, double b)
    {
    return fabs(a - b) <= EPSILON || a == b;
    }
    

/**
*@brief function responsible for a, b, c coefficients input
*
*@detail function gets pointers of the a, b, c coeffcients of the square equation
*@param a ax2
*@param b bx
*@param c c
*@return 0 if inputting values are valid else itself until user inputs valid values
*/
int input(double* a, double* b, double* c)
	{
	printf("Enter the coefficients of the square equation\n");
	int is_correct = scanf("%lg %lg %lg", a, b, c);

	if (a == NULL || b ==NULL || c == NULL)
        is_correct = 0;

	if (is_correct != 3)
        {
        skip_symb();
        printf("Invalid values. Try again\n");
        return input(a, b, c);
        }
	return 0;
	}

	
///function that skips unreadable symbols after bad input
void skip_symb(void)
	{
	char curr_symb = ' ';
    while (curr_symb != '\n')
        curr_symb = getchar();	
	}


/**
*@brief function that display roots of square equation (if they are) else "No roots" or "Infinite amount of roots" 
*
*@detail function gets the root amount of the square equation solving and values of these roots
*@param root_amount the quantity of solves
*@param x1 the first root
*@param x2 the second root
*/
void output(int root_amount, double x1, double x2)
    {
    switch(root_amount)
		{

		case NO_ROOTS:
            printf("No roots");
            break;

		case ONE_ROOT:
            printf("x=%lg", x1);
            break;

		case TWO_ROOTS:
            printf("x1=%lg, x2=%lg", x1, x2);
            break;

		case INF_ROOTS:
            printf("Infinite amount of roots");
            break;

		}
    }
    

/**
*@brief function that tests square equation solving function
*
*@detail function calls curr_test() several times and displays the result (how many calls were succesfull)
*/
void square_test(void)
	{
	int test_amount = 10;
	double test_input[test_amount][6]
    	{
    	{0, 0, 0, INF_ROOTS, NAN, NAN}, //	0 0 0
    	{0, 0, 4, NO_ROOTS, NAN, NAN},	//	0 0 1
    	{0, 5, 0, ONE_ROOT, 0, NAN},	//	0 1 0
    	{0, 2, 1, ONE_ROOT, -0.5, NAN},	//	0 1 1
    	{0, 0, 1, NO_ROOTS, NAN, NAN},	//  1 0 0
    	{5, 0, 4, NO_ROOTS, NAN, NAN},	//  1 0 1
    	{3, 6, 0, TWO_ROOTS, -2, 0},	//  1 1 0
    	{1, -6, 8, TWO_ROOTS, 2, 4},	//  1 1 1 d>0
    	{1, -2, 1, ONE_ROOT, 1, NAN},	//  1 1 1 d == 0
    	{4, 1, 1, NO_ROOTS, NAN, NAN}	//  1 1 1 d < 0
		};	
		
	int results = 0;
	
	for (int i = 0; i < 10; i++)
		results += curr_test(test_input[i][0], test_input[i][1], test_input[i][2], test_input[i][3], test_input[i][4], test_input[i][5]);
	
	printf("\n%d/%d tests completed succesfully", results, test_amount);
	}

	
/**
*@brief function that do only one separate test
*
*@detail Tests function solve(). It gets a, b, c coefficients of the square equation, 
*correct(!!!) root amount of equation and correct roots of equation.
*@param a ax2
*@param b bx
*@param c c
*@param expected_root_amount correct quantity of solves of the equation
*@param expected_x1 the first correct root of the equation
*@param expected_x2 the second correct root of the equation
*If current equation doesn't have second root or roots in all, input NAN to root params
*If there are 2 roots, expected_x1 should be bigger than expected_x2
*@return 1 if test completes succesfully else 0(also outputs the message in console) 
*/	
int curr_test(double a, double b, double c, int expected_root_amount, double expected_x1, double expected_x2)
	{
	double real_x1 = NAN, real_x2 = NAN;
	int real_root_amount = solve(a, b, c, &real_x1, &real_x2);
	
	if (!(real_root_amount == expected_root_amount))
		{
		printf("\nTest (%lg, %lg, %lg) completed UNsuccesfully."
		"Expected %d root(s), %lg, %lg but program returned %d roots, %lg, %lg. Cringe...\n",\
		 a, b, c, expected_root_amount, expected_x1, expected_x2, real_root_amount, real_x1, real_x2);
		return 0;
		}
	else
		switch(real_root_amount)
			{
				
			case NO_ROOTS:
				printf("\nTest (%lg, %lg, %lg) completed succesfully\n", a, b, c);
				return 1;
			
			case ONE_ROOT:
				if ((is_equal(expected_x1, real_x1)) || (isnan(expected_x1) && isnan(real_x1)))
					{
					printf("\nTest (%lg, %lg, %lg) completed succesfully\n", a, b, c);
					return 1;
					}
				else
					{
					printf("\nTest (%lg, %lg, %lg) completed UNsuccesfully."
					"Expected 1 root: %lg but program returned %lg. Cringe...\n",\
		 			a, b, c, expected_x1, real_x1);
					return 0;
					}
							
			case TWO_ROOTS:
				if (((is_equal(expected_x1, real_x1)) || (isnan(expected_x1) && isnan(real_x1))) &&\
				((is_equal(expected_x2, real_x2)) || (isnan(expected_x2) && isnan(real_x2))))
					{
					printf("\nTest (%lg, %lg, %lg) completed succesfully\n", a, b, c);
					return 1;
					}
				else
					{
					printf("\nTest (%lg, %lg, %lg) completed UNsuccesfully."
					"Expected 2 roots: %lg, %lg but program returned %lg, %lg. Cringe...\n",\
		 			a, b, c, expected_x1, expected_x2, real_x1, real_x2);
					return 0;
					}
						
			case INF_ROOTS:
				printf("\nTest (%lg, %lg, %lg) completed succesfully\n", a, b, c);
				return 1;
				
			}
	}
		
	

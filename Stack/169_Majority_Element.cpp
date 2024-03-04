// Problem Link:
// https://leetcode.com/problems/majority-element/?envType=daily-question&envId=2024-02-15

import "fmt"

type stack []int

func (s *stack) size() int {
	return len(*s)
}

func (s *stack) isEmpty() bool {
	if len(*s) == 0 {
		return true
	}

	return false
}

func (s *stack) push(value int) {
	*s = append(*s, value)
}

func (s *stack) pop() {
	ok := s.isEmpty()

	if !ok {
		index := len(*s) - 1
		*s = (*s)[:index]
	}
}

func (s *stack) top() (int, error) {
	index := len(*s) - 1

	if index > -1 {
		return (*s)[index], nil
	}

	return 0, fmt.Errorf("empty stack")
}

func isOperator(s string) bool {
	if s == "+" || s == "-" || s == "*" || s == "/" {
		return true
	}

	return false
}

func operatorToCalculate(s string, sum int, operand int) int {
	switch s {
	case "+":
		return operand + sum
	case "-":
		return operand - sum
	case "*":
		return operand * sum
	default:
		if sum == 0 {
			return 0
		}
		return operand / sum
	}
}

func evalRPN(tokens []string) int {
	var st stack

	for _, token := range tokens {
		if isOperator(token) {
			sum, _ := st.top()
			st.pop()
			operand, _ := st.top()
			st.pop()

			sum = operatorToCalculate(token, sum, operand)
			st.push(sum)
		} else {
			s, _ := strconv.Atoi(token)
			st.push(s)
		}
	}

	ans, _ := st.top()
	return ans
}
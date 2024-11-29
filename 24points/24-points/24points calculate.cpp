#include"24 points.h"

bool isEqualTo24(double result) {
	return fabs(result - 24.0) < 1e-6; // 判断是否接近24
}
template <typename T>
vector<vector<T>> permute(vector<T>& v) {
    vector<vector<T>> result;
    sort(v.begin(), v.end());
    do {
        result.push_back(v);
    } while (next_permutation(v.begin(), v.end()));
    return result;
}
string toString(double a, double b, char op) {
	stringstream ss;
	ss << "(" << a << " " << op << " " << b << ")";
	return ss.str();
}
vector<char> operators = { '+', '-', '*', '/' };
vector<string> parenthesesForms = {
    "((a o b) u c) v d",
    "(a o (b u c)) v d",
    "(a o b) u (c v d)",
    "a o ((b u c) v d)",
    "a o (b u (c v d))"
};

// 替换占位符
string replacePlaceholder(string expr, const vector<double>& perm, char op1, char op2, char op3) {
    stringstream ss;
    for (char& c : expr) {
        if (c == 'a') ss << perm[0];
        else if (c == 'b') ss << perm[1];
        else if (c == 'c') ss << perm[2];
        else if (c == 'd') ss << perm[3];
        else if (c == 'o') ss << op1;
        else if (c == 'u') ss << op2;
        else if (c == 'v') ss << op3;
        else ss << c;
    }
    return ss.str();
}
void deal(string tmp, vector<string>& term) {
    istringstream iss(tmp);
    vector<double> numbers;
    double num;
    while (iss >> num) {
        numbers.push_back(num);
    }
    auto allPermutations = permute(numbers);

    // 枚举运算符组合
    for (auto& perm : allPermutations) {
        for (char op1 : operators) {
            for (char op2 : operators) {
                for (char op3 : operators) {
                    // 穷举括号结构
                    for (const string& form : parenthesesForms) {
                        // 将运算符应用到括号结构中
                        string expression = replacePlaceholder(form, perm, op1, op2, op3);
                        // 计算表达式
                        if(isEqualTo24(calculate(expression)))
                            term.push_back(expression);
                        
                    }
                }
            }
        }
        
    }
}





int main() {
	vector<string> term;
	ifstream infile;
	infile.open("E:\\12.txt");
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
	string tmp;
	while(getline(infile, tmp)) {
		deal(tmp,term);
	}
    infile.close();

    for (int i = 0; i < term.size(); i++) {
        cout << term[i] << endl;
    }
    return 0;
}
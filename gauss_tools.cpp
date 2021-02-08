#include "gauss_tools.hpp"

// works
string format_row(string row) {
	for(int i = 0; i < row.length(); i++) {
		if(row[i] == ' ')
			row.erase(i--, 1);
		else
			break;
	}

	if(row.length() < 2)
		return row;

	char previos = row[0];

	for(int i = 1; i < row.length(); i++) {
		if(previos == ' ' && row[i] == ' ') {
			row.erase(i - 1, 1);
			--i;
			if(i == (row.length() - 1)) {
				row.erase(i, 1);
				--i;
			}
		}
		else if(previos == ' ' && row[i] == '\n') {
			row.erase(i - 1, 1);
			--i;
		}
		previos = row[i];
	}

	if(row[row.length() - 1] == ' ')
		row.erase(row.length() - 1, 1);
	if(row[row.length() - 1] != '\n')
		row += '\n';

	return row;
}

string format_matrix(string filename, int *num_rows, int *num_cols) {
	ifstream fin(filename);

	if(!fin.is_open()) {
		cout << "Errors~!" << endl;
		return "NULL";
	}

	(*num_rows) = 0, (*num_cols) = 0;
	char ch;
	int j = 0;
	stringstream ss;
	float buff_value;
	string buff_row, matrix = "";

	while(!fin.eof()) {
		getline(fin, buff_row);

		buff_row = format_row(buff_row);

		if(buff_row == "" || buff_row == "\n")
			continue;

		ss.str(buff_row);

		while(!ss.eof()) {
			ss >> buff_value;
			++j;

			ss.get(ch);
			if(ch == '\n') {
				if(!(*num_cols)) {
					matrix += buff_row;
					(*num_cols) = j;
				}
				else if(j != (*num_cols))
					--(*num_rows);
				else
					matrix += buff_row;

				j = 0;
				break;
			}
		}

		++(*num_rows);
	}

	if(j != 0)
		(*num_rows)++;

	fin.close();

	return matrix;
}

float** read_matrix(string filename, int *num_rows, int *num_cols) {
	string matrix = format_matrix(filename, num_rows, num_cols);

	if(matrix == "NULL")
		return NULL;

	float **M = new float*[(*num_rows)];
	for(int i = 0; i < (*num_rows); i++)
		M[i] = new float[(*num_cols)];

	stringstream ss(matrix);

	for(int i = 0; i < (*num_rows); i++)
		for(int j = 0; j < (*num_cols); j++)
			ss >> M[i][j];

	return M;
}

bool is_linear_relationship(float **M, int num_rows, int num_cols) {
	bool is_lr;
	float factor;

	for(int i = 0; i < num_rows; i++)
		for(int j = i + 1; j < num_rows; j++) {
			is_lr = true;
			factor = M[i][0] / M[j][0];
			for(int k = 1; k < num_cols; k++) {
				if((M[i][k] / M[j][k]) != factor) {
					is_lr = false;
					break;
				}
			}
			if(is_lr)
				return is_lr;
		}

	return is_lr;
}

void copy_matrix(float **from_M, int num_rows, int num_cols, float **to_M) {
	for(int i = 0; i < num_rows; i++)
		for(int j = 0; j < num_cols; j++)
			to_M[i][j] = from_M[i][j];
	return;
}

float** gauss_convert(float **M, int num_rows, int num_cols) {
	if(is_linear_relationship(M, num_rows, num_cols)) {
		cout << "Convertion is not possible~!" << endl;
		return NULL;
	}

	float **conversed_M = new float*[num_rows];
	for(int i = 0; i < num_rows; i++)
		conversed_M[i] = new float[num_cols];

	copy_matrix(M, num_rows, num_cols, conversed_M);

	float factor;
	int num_steps = (num_rows < num_cols - 1) ? num_rows : num_cols - 1;

	for(int i = 0; i < num_steps; i++) {
		factor = conversed_M[i][i];
		for(int j = 0; j < num_cols; j++)
			conversed_M[i][j] /= factor;


		for(int j = i + 1; j < num_rows; j++) {
			factor = conversed_M[j][i];
			for(int k = 0; k < num_cols; k++)
				conversed_M[j][k] -= conversed_M[i][k] * factor;
		}
	}

	for(int i = num_steps - 1; i > 0; i--)
		for(int j = i - 1; j >= 0; j--) {
			factor = conversed_M[j][i];
			for(int k = i; k < num_cols; k++) {
				conversed_M[j][k] -= conversed_M[i][k] * factor;
			}
		}

	return conversed_M;
}

void list_matrix(float **M, int num_rows, int num_cols) {
	for(int i = 0; i < num_rows; i++){
		for(int j = 0; j < num_cols; j++) {
			cout << ((j == num_cols - 1) ? "| " : "") << M[i][j] << ((j == num_cols - 1) ? "" : " ");
		}
		cout << endl;
	}
	return;
}
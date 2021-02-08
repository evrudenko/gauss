#include "gauss_tools.cpp"

int main(int argc, char const *argv[]) {
	if(argc != 2) {
		cout << "Right call: " << *argv << " filename.txt";
		return 1;
	}

	int n, m;
	float **M = read_matrix(argv[1], &n, &m);

	if(!M) {
		cout << "Can not read the file: " << argv[1] << "!" << endl;
		return 1;
	}

	float **gauss_M = gauss_convert(M, n, m);

	list_matrix(M, n, m);

	cout << "After: " << endl;

	if(gauss_M)
		list_matrix(gauss_M, n, m);

	for(int i = 0; i < n; i++)
		delete[] M[i];
	delete[] M;

	for(int i = 0; i < n; i++)
		delete[] gauss_M[i];
	delete[] gauss_M;

	return 0;
}
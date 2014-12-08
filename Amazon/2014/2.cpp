#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector < int > convertMatrix(int width, int height, vector < int > matrix) {
    vector<int> res;
    set<int> s;
    vector<vector<int> > v;
    
    for (int i = 0; i < height; i++) {
        vector<int> tmp;
        for (int j = 0; j < width; j++) {
            tmp.push_back(matrix[i * width + j]);
        }
        v.push_back(tmp);
    }

    int i = 0;
    int j = 0;
    while (1) {
        // right
        while (1) {
            if (j == width) {
                j = width - 1;
                break;
            }
            if (s.find(v[i][j]) != s.end()) {
                j--;
                break;
            }
            res.push_back(v[i][j]);
            s.insert(v[i][j]);
            j++;
        }
        

        // left down
        i++, j--;
        while (1) {
            if (i == height) {
                i = height - 1;
                j++;
                break;
            }
            if (j == -1) {
                i--;
                j = 0;
                break;
            }
            if (s.find(v[i][j]) != s.end()) {
                i--, j++;
                break;
            }
            res.push_back(v[i][j]);
            s.insert(v[i][j]);
            i++, j--;
        }
       
        // left
        j--;
        while (1) {
            if (j == -1) {
                j = 0;
                break;
            }
            if (s.find(v[i][j]) != s.end()) {
                j++;
                break;
            }

            res.push_back(v[i][j]);
            s.insert(v[i][j]);
            j--;
        }
        

        // up
        i--;
        while (1) {
            if (i == -1) {
                i = 0;
                break;
            }
            if (s.find(v[i][j]) != s.end()) {
                i++;
                break;
            }

            res.push_back(v[i][j]);
            s.insert(v[i][j]);
            i--;
        }
        
        j++;
        if (j > width || s.find(v[i][j]) != s.end()) {
            break;
        }
    }

    return res;
}

int main() {
    vector<int> res;
    int _width;
    cin >> _width;

    int _height;
    cin >> _height;

    vector<int> _matrix;
    int _matrix_item;
    for (int _matrix_i = 0; _matrix_i < _width * _height; _matrix_i++) {
        cin >> _matrix_item;
        _matrix.push_back(_matrix_item);
    }

    res = convertMatrix(_width, _height, _matrix);
    for (int res_i = 0; res_i <res.size(); res_i++) {
        cout << res[res_i] << " ";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to preprocess the pattern and compute the longest prefix suffix array
vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m);
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// Function to perform KMP search
void kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps = computeLPSArray(pattern);

    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern occurs at shift: " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ABAAABCD";
    string pattern = "ABC";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    kmpSearch(text, pattern);

    return 0;
}


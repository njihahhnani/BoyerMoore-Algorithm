#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;  // Using directive to avoid std:: prefix

// Function to preprocess the bad character heuristic
void badCharHeuristic(const string &pattern, vector<int> &badChar) {
    int m = pattern.size();  // Length of the pattern
    fill(badChar.begin(), badChar.end(), -1);  // Initialize all entries of badChar to -1

    // Fill badChar array with the position of last occurrence of each character in pattern
    for (int i = 0; i < m; ++i) {
        badChar[(int)pattern[i]] = i;  // Store the index of the character's last occurrence
    }
}

// Function to preprocess the good suffix heuristic
void goodSuffixHeuristic(const string &pattern, vector<int> &suffix, vector<int> &goodSuffix) {
    int m = pattern.size();  // Length of the pattern
    vector<int> borderPos(m + 1, 0);  // Border position array
    int i = m;  // Initialize i to length of the pattern
    int j = m + 1;  // Initialize j to length of the pattern + 1
    borderPos[i] = j;  // Set the last position of borderPos to j

    // Preprocessing the border positions
    while (i > 0) {
        // Find the largest border of the suffix ending at position i-1
        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
            if (goodSuffix[j] == 0) {
                goodSuffix[j] = j - i;  // If goodSuffix[j] is not set, set it to the shift amount
            }
            j = borderPos[j];  // Update j to the border position
        }
        --i;
        --j;
        borderPos[i] = j;  // Update borderPos for current i
    }

    j = borderPos[0];  // Start from the border position of the first character
    // Preprocessing the good suffix array
    for (i = 0; i <= m; ++i) {
        if (goodSuffix[i] == 0) {
            goodSuffix[i] = j;  // If goodSuffix[i] is not set, set it to j
        }
        if (i == j) {
            j = borderPos[j];  // Update j to the border position of j
        }
    }
}

// Function to perform Boyer-Moore search using bad character heuristic
void boyerMooreBadChar(const string &text, const string &pattern) {
    int n = text.size();  // Length of the text
    int m = pattern.size();  // Length of the pattern
    vector<int> badChar(256, -1);  // Bad character heuristic array
    badCharHeuristic(pattern, badChar);  // Preprocess bad character heuristic

    int s = 0;  // s is the shift of the pattern with respect to the text
    // Searching the pattern in text using bad character heuristic
    while (s <= (n - m)) {
        int j = m - 1;  // Start comparing from the end of the pattern
        // Move backward in the pattern and text as long as characters are matching
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        if (j < 0) {
            // If the pattern is present at the current shift, print the shift value
            cout << "Pattern occurs at shift (Bad Char): " << s << endl;
            // Shift the pattern to align with the next occurrence using bad character heuristic
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            // Shift the pattern such that the mismatched character in the text
            // aligns with the last occurrence of it in the pattern or move by one if not present
            s += max(1, j - badChar[text[s + j]]);
        }
    }
}

// Function to perform Boyer-Moore search using good suffix heuristic
void boyerMooreGoodSuffix(const string &text, const string &pattern) {
    int n = text.size();  // Length of the text
    int m = pattern.size();  // Length of the pattern
    vector<int> suffix(m + 1, 0);  // Suffix array
    vector<int> goodSuffix(m + 1, 0);  // Good suffix array
    goodSuffixHeuristic(pattern, suffix, goodSuffix);  // Preprocess good suffix heuristic

    int s = 0;  // s is the shift of the pattern with respect to the text
    // Searching the pattern in text using good suffix heuristic
    while (s <= (n - m)) {
        int j = m - 1;  // Start comparing from the end of the pattern
        // Move backward in the pattern and text as long as characters are matching
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        if (j < 0) {
            // If the pattern is present at the current shift, print the shift value
            cout << "Pattern occurs at shift (Good Suffix): " << s << endl;
            // Shift the pattern to align with the next occurrence using good suffix heuristic
            s += goodSuffix[0];
        } else {
            // Shift the pattern such that the mismatched character in the text
            // aligns with the last occurrence of a suffix in the pattern or move by one
            s += goodSuffix[j + 1];
        }
    }
}

int main() {
    string text = "ABAAABCD";
    string pattern = "ABC";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    boyerMooreBadChar(text, pattern);  // Search pattern in text using bad character heuristic
    boyerMooreGoodSuffix(text, pattern);  // Search pattern in text using good suffix heuristic

    return 0;
}

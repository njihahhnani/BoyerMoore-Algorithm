# CPT212 Assignment 2

### Group Members
1. Bernadette Lee Pei Chen
2. Khoo Iu Wan
3. Najihah Hanani binti Ahmad Farid
4. Nur Nabila binti Normiza Shahman

### Boyer-Moore Algorithm

The `boyermoore.cpp` file implements the Boyer-Moore string searching algorithm using two heuristic techniques: the bad character heuristic and the good suffix heuristic. These methods are designed to efficiently locate occurrences of a pattern within a text.

1. **Bad Character Heuristic**: Preprocesses the pattern to efficiently handle mismatches by focusing on the last occurrence of characters in the pattern.

2. **Good Suffix Heuristic**: Another preprocessing step that optimizes shifts in case of mismatches by leveraging matching suffixes within the pattern.

The main function then applies these heuristics to search for a specific `pattern` within a `text`. It prints out the positions (shifts) where the pattern is found using each heuristic method. Overall, this implementation demonstrates how preprocessing based on pattern characteristics can significantly improve the efficiency of substring searches in large texts.

### Knuth-Morris-Pratt (KMP) 

THE `kmp algo.cpp` file implements the Knuth-Morris-Pratt (KMP) algorithm for string searching. It efficiently finds occurrences of a pattern within a text using the longest prefix suffix (LPS) array to avoid unnecessary comparisons. The `kmpSearch` function searches for the pattern and prints the starting indices of matches. The `main` function demonstrates this by searching for a pattern in a given text.

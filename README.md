🌐 Mini Web Browser (DSA Project)
Team DEAD (Team-12)

A Data Structures & Algorithms project implementing a mini command-line Web Browser using Stacks, BST, Priority Queue (Max-Heap), and Graphs.

👨‍💻 Team Members
SRN	Name
PES2UG24CS154	Dhanush Sai Suprapadha
PES2UG24CS166	G S Dheekshith
PES2UG24CS173	Yekambar Eshwar Rao
🚀 Project Overview

This project implements a Mini Web Browser simulation using fundamental DSA concepts:

✔️ Stacks

Browsing history

Back & Forward navigation

✔️ Binary Search Tree

Storing & indexing page titles

Word search

Word frequency counting

✔️ Priority Queue (Max-Heap)

Ranking words based on frequency

Highest-frequency words displayed first

✔️ Graph (Adjacency List)

Hyperlinks between pages

Viewing page connectivity

🧩 Features
🔹 1. Open Pages

Stores the page in browser history.

🔹 2. Back / Forward Navigation

Uses two stacks (history + forward).

🔹 3. Add Hyperlinks

Creates directed edges between pages.

🔹 4. Show Hyperlinks

Displays adjacency lists for the selected page.

🔹 5. Index Page Titles

Breaks titles into words → stores them in a BST.

🔹 6. Search Keyword

Searches the BST for a word and displays frequency.

🔹 7. Word Ranking

Uses a Max Heap priority queue to rank words.

🛠️ Technologies & Concepts Used
Concept	Implementation
Stack	Array-based stack for history
BST	Stores & counts word frequency
Priority Queue	Max-Heap for ranking words
Graph	Adjacency list for hyperlinks
Tokenization	strtok() for splitting words
📂 Project Structure
DSA-Project/
│
├── browser.h         # All struct definitions & function prototypes
├── browser.c         # Stack + BST + PQ + Graph + Navigation logic
├── main.c            # Menu-driven interface
├── README.md         # Project documentation

📸 Functionality Demo (CLI Menu)
===== MINI WEB BROWSER =====
1. Open Page
2. Back
3. Forward
4. Add Hyperlink
5. Show Hyperlinks
6. Index Page Title
7. Search Keyword
8. Rank Words (PQ)
9. Exit

🔍 Example: Word Ranking

Input Title:

data structures in browser using bst and priority queue browser project


Rank Output:

1. browser (freq = 2)
2. data (freq = 1)
3. structures (freq = 1)
...

🧪 How to Compile & Run
Compile
gcc main.c browser.c -o browser

Run
./browser

⭐ What We Learned

Building DSA-based real applications

Implementing multiple data structures in one project

Efficient searching, ranking, and storing data

Handling pointers, dynamic memory, tokenization

🏁 Conclusion

This project demonstrates how classical DSA concepts can be used to simulate real browser features such as:

Navigation

Keyword indexing

Ranking

Connectivity

The entire system is modular, extendable, and demonstrates strong understanding of DSA + C programming.

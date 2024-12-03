# File Compression Project

## Overview  
This project, completed as part of the Data Structures and Algorithms (DSA) coursework, focuses on implementing file compression techniques using **Huffman Coding** and **Run-Length Encoding (RLE)**. Both methods are lossless compression algorithms, aiming to reduce file size without losing any data. The implementation leverages **C++**, employing Object-Oriented Programming (OOP) principles and data structures like arrays, hash maps, and min-heaps.

## Objectives  
- **Understand the fundamentals** of data structures and algorithms and their application to real-world problems.  
- **Implement lossless file compression** algorithms in C++ for text, image, and video files.  
- **Analyze and compare compression efficiency** between Huffman Coding and Run-Length Encoding.  
- **Collaborate as a team** to solve complex problems by dividing tasks effectively.

## Features  
- Compression of files using **Huffman Coding**:  
  - Assigns variable-length codes based on symbol frequency.  
  - Uses a binary tree structure for encoding and decoding.  
- Implementation of **Run-Length Encoding**:  
  - Encodes sequences of repeated characters into a compressed form.  
- Testing on different file types (text, image, video) to evaluate performance.  
- Hands-on use of **priority queues**, **binary trees**, and **hash maps** for efficient data processing.  

## Applications  
- File storage: Reduced size for efficient storage.  
- File transfer: Faster transmission over networks.  
- Multimedia: Compressing images, videos, and text without quality loss.  
- Gaming and software distribution: Faster downloads with compressed assets.  
- Database management: Optimized storage for large datasets.  

## Technical Stack  
- **Programming Language**: C++  
- **Libraries Used**:  
  - **STL**: Min-heap, hash maps for data structures.  
  - **External References**: Assorted materials from *Grokking Algorithms* and *Data Structures and Algorithms Made Easy*.  

### Data Structures Utilized  
- **Min-Heap**: Priority queue for selecting minimum frequency nodes.  
- **Binary Tree**: Huffman tree for encoding and decoding.  
- **Hash Map**: Key-value storage for encoding table.  
- **Array**: Storage of raw data and frequency calculations.  

## Implementation Workflow  
1. **Frequency Analysis**: Compute character frequencies in the input file.  
2. **Min-Heap Construction**: Store frequency nodes in a priority queue.  
3. **Huffman Tree Creation**: Iteratively build the binary tree for encoding.  
4. **Encoding**: Replace characters with corresponding binary codes.  
5. **Compression**: Store encoded binary data to reduce size.  
6. **Decompression**: Decode binary data back to the original format.  

## Results  
- Successfully implemented both **Huffman Coding** and **Run-Length Encoding** for file compression.  
- Achieved significant file size reduction for various datasets.  
- Demonstrated efficient encoding/decoding with minimal computational overhead.  

## Limitations and Future Enhancements  
### Limitations  
- Fixed heap size, limiting scalability.  
- Suboptimal handling of duplicate values.  
- Performance bottlenecks with unbalanced binary trees.  

### Future Enhancements  
- Implementing dynamic heaps (e.g., Fibonacci or pairing heaps).  
- Enhancing duplicate value handling.  
- Adding dynamic heap resizing for improved flexibility and memory usage.  

## References  
### Books  
1. *Grokking Algorithms* by Aditya Y. Bhargava  
2. *Data Structures and Algorithms Made Easy* by Narasimha Karumanchi  

### Online Resources  
1. [YouTube: Huffman Coding Algorithm](https://www.youtube.com/watch?v=co4_ahEDCho)  
2. [YouTube: Data Compression Concepts](https://www.youtube.com/watch?v=B3y0RsVCyrw)  

---

This project provided valuable insights into **data compression algorithms** and their practical applications. It also honed our teamwork and problem-solving skills, contributing significantly to our understanding of core DSA concepts.

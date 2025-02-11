# DicTranslator: Fusion of Dictionary and Translator

## Project Overview
This project is a fusion of a **dictionary** and a **translator**, implemented using **C++** with an **unordered map** data structure and **MySQL database management**. The dictionary provides:
- **Hindi meanings** of English words
- **Antonyms and synonyms** for each word
- **Efficient data retrieval** using an unordered map
- **Database connectivity** for persistent storage
- **Manual database updates** for flexibility

The dictionary fetches data from a MySQL database and stores it in an unordered map for quick lookups. Users can search for words and view their translations, antonyms, and synonyms. If a word is not found, they can **manually add** it to the database.

---

## Features
✅ **Fast lookups** using an unordered map (O(1) average time complexity)
✅ **Hindi translations** for English words
✅ **Antonyms & Synonyms** support
✅ **User-friendly console interface**
✅ **Database connectivity** with MySQL for data persistence
✅ **Option to add new words** dynamically
✅ **Well-structured menu for easy navigation**
✅ **Case-insensitive search** for better usability
✅ **Error handling** for database connectivity

---

## Technologies Used
- **Programming Language:** C++
- **Database:** MySQL
- **Libraries Used:**
  - `<unordered_map>` for fast lookups
  - `<mysql.h>` for database interaction
  - `<algorithm>` for string operations
  - `<windows.h>` for console styling (Windows-specific)

---

## How It Works
1. **Connect to MySQL Database**: The program initializes a connection to a MySQL database.
2. **Fetch Data**: It retrieves word mappings from the `bilingual_dictionary` table and stores them in an unordered map.
3. **User Menu**:
   - **Option 1:** Search for an English word to get its Hindi meaning, antonyms, and synonyms.
   - **Option 2:** Exit the program.
4. **Case-Insensitive Search**: The program converts the input word to lowercase before searching.
5. **Add New Words**: If a word is not found, users can add its translation and related words to the dictionary.
6. **Update Database**: Newly added words are inserted into the MySQL database.
7. **Exit Gracefully**: The program closes the database connection before exiting.

---

## Installation & Setup
### Prerequisites
- **C++ Compiler** (GCC, MSVC, or Clang)
- **MySQL Server** installed and running
- **MySQL Connector for C++**

### Steps to Run
1. Clone the repository or download the source code.
2. Install MySQL and create a database named `dict`.
3. Create a table `bilingual_dictionary` using the following SQL command:
```sql
CREATE TABLE bilingual_dictionary (
    id INT AUTO_INCREMENT PRIMARY KEY,
    english_word VARCHAR(255) UNIQUE,
    hindi_translation VARCHAR(255),
    antonyms VARCHAR(255),
    synonyms VARCHAR(255)
);
```
4. Insert sample data:
```sql
INSERT INTO bilingual_dictionary (english_word, hindi_translation, antonyms, synonyms)
VALUES ('happy', 'खुश', 'sad', 'joyful, delighted');
```
5. Compile the C++ program:
```bash
g++ dictionary.cpp -o dictionary -lmysql
```
6. Run the program:
```bash
./dictionary
```

---

## Future Enhancements
🔹 **GUI-based Dictionary** using Qt or Tkinter
🔹 **API Integration** for real-time translations
🔹 **Support for more languages** beyond Hindi
🔹 **Voice-based search** for ease of use
🔹 **Enhanced database operations** for better scalability

---

## Conclusion
This dictionary project efficiently combines translation and word relationships using **C++ unordered maps** and **MySQL database management**. It provides **fast lookups, an interactive UI, and a scalable approach** to word storage and retrieval. With further improvements, it can become a powerful multilingual dictionary tool!

---

💡 **Contributors**: Mittal Soni
📧 **Contact**: mittalsoni212@gmail.com


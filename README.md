# smart-attendance-management-system-GitHub
Description:
This project is a Student Attendance Management System developed using the C programming language.
It allows teachers or users to manage student attendance efficiently using file handling.
The system can:
Record attendance for 7 consecutive days starting from a given date
Store attendance data permanently using files
Search student records by roll number
Calculate attendance percentage automatically
Display a warning if attendance is below 75%
Delete a student’s attendance record by roll number
Features:
Date-wise attendance input for 7 days
Automatic attendance percentage calculation
File-based data storage
Search student by roll number
Delete student record
Menu-driven and user-friendly interface.
## How to Run the Project

Follow these steps to run the Student Attendance Management System:

1. **Download or Clone the Repository**
   - Click the green "Code" button in GitHub and copy the repository link
   - Or download the repository as a ZIP file and extract it

2. **Open a Terminal or Command Prompt**
   - Navigate to the folder where `attendance.c` is located

3. **Compile the Program**
   - Use a C compiler like GCC:
     ```
     gcc attendance.c -o attendance
     ```

4. **Run the Program**
   - Execute the compiled program:
     ```
     ./attendance      (on Linux or macOS)
     attendance.exe    (on Windows)
     ```

5. **Follow On-Screen Instructions**
   - Enter the start date in DD-MM-YYYY format
   - Input the total number of students
   - Enter attendance for each student (1 = Present, 0 = Absent)
   - Use the menu to search, delete, or exit

6. **Check Attendance Records**
   - All records are stored in `attendance_data.txt` in the same folder

# Page Table Translator

A console-based Operating Systems mini project that simulates **logical address to physical address translation using one-level paging and a page table**.

This project was developed for the Operating Systems module to demonstrate how an operating system can divide logical memory into pages, map those pages to physical memory frames, and translate logical addresses into physical addresses.

---

## 1. Project Overview

The **Page Table Translator** simulates the basic address translation process used in a paged virtual memory system.

The user can:

* Configure the page size at the beginning of a simulation.
* Configure the number of physical frames.
* Create a page-to-frame mapping manually.
* View the current page table.
* Translate one or more logical addresses.
* Calculate the page number and offset.
* Find the corresponding physical frame.
* Calculate the physical address.
* Detect page faults when a page is not loaded.
* Start a new simulation without restarting the program.
* Exit the program safely.

The project uses **one-level paging only**. No page replacement algorithm is implemented because it is not required for the Page Table Translator.

---

## 2. Main Concepts Demonstrated

The program demonstrates the following Operating Systems concepts:

* Virtual memory
* Logical addresses
* Physical addresses
* Paging
* Pages and frames
* Page tables
* Page number calculation
* Offset calculation
* Address translation
* Page faults
* Logical-to-physical address conversion

The basic translation process is:

```text
Logical Address
      │
      ▼
┌───────────────┐
│ Page Number   │
│ Offset        │
└───────────────┘
      │
      ▼
   Page Table
      │
      ▼
 Frame Number
      │
      ▼
Physical Address
```

The page number is obtained by dividing the logical address by the page size, while the offset is obtained from the remainder.

The physical address is then calculated using the mapped frame and the offset.

---

## 3. Features

### Simulation Configuration

At the beginning of each simulation, the user can configure:

* Page size
* Number of physical frames
* Number of pages currently loaded
* Page-to-frame mappings

The available page-size choices are restricted according to the project requirements, with **1024 bytes (1 KB) as the maximum allowed page size**.

### Page Table

The program creates a page table containing up to 16 pages.

Each page can either:

* Be mapped to a physical frame, or
* Remain `UNMAPPED`

The program also prevents the same physical frame from being assigned to multiple pages.

### Address Translation

The user can translate up to **12 logical addresses per translation run**.

For each address, the program displays:

* Logical Address
* Page Number
* Offset
* Frame Number, when available
* Physical Address, when translation is successful
* Page Fault message, when the page is not loaded

### Input Validation

The program validates user input for:

* Page size
* Number of frames
* Number of loaded pages
* Page numbers
* Frame numbers
* Menu choices
* Logical addresses
* Number of addresses to translate
* Duplicate page mappings
* Duplicate frame mappings

Invalid logical addresses are rejected instead of being incorrectly treated as page faults.

### Main Menu

After the simulation is configured, the user can:

```text
1. Display Page Table
2. Translate Address
3. New Simulation
4. Exit
```

This allows multiple translations to be performed using the same page table without having to recreate the simulation after every translation.

---

## 4. Project Constraints

The implementation follows the main constraints given in the project specification.

| Requirement                  | Implementation               |
| ---------------------------- | ---------------------------- |
| Maximum logical pages        | 16                           |
| Maximum page size            | 1024 bytes (1 KB)            |
| Physical frames              | 8–16                         |
| Paging type                  | One-level paging             |
| Maximum translations per run | 12                           |
| Page replacement             | Not required                 |
| Page fault handling          | Displays Page Fault Occurred |
| Page table                   | Manually configured by user  |
| Application type             | Console-based                |

---

## 5. Requirements

To compile and run the project, you need:

* A C compiler
* A terminal or command prompt
* A system that supports standard C input/output

The program uses:

```c
#include <stdio.h>
#include <stdbool.h>
```

ANSI escape codes are also used for coloured console output. On terminals that do not support ANSI colours, the program logic will still work, although the colours may not be displayed correctly.

---

## 6. Project Structure

The project is intentionally kept simple because it is a small console-based simulation.

```text
Page-Table-Translator/
│
├── main.c
└── README.md
```

### `main.c`

Contains the complete implementation, including:

* Simulation configuration
* Page table creation
* Input validation
* Address translation
* Page fault detection
* Physical address calculation
* Menu handling
* Console output

---

## 7. Important Functions

Some of the main functions used in the program are:

### `getPageSize()`

Allows the user to select the page size used by the current simulation.

### `getFrameCount()`

Gets the number of physical frames and ensures that it remains within the allowed range.

### `createPageTable()`

Initializes the page table and allows the user to manually create page-to-frame mappings.

### `calculatePageNumber()`

Calculates the page number from a logical address.

### `calculateOffset()`

Calculates the offset within the page.

### `getPhysicalAddress()`

Uses the frame number and offset to calculate the physical address.

### `isPageFault()`

Checks whether the required page is currently mapped to a physical frame.

### `translateLogicalAddress()`

Handles the complete logical-to-physical address translation process.

### `displayPageTable()`

Displays the current page table and its page-to-frame mappings.

---

## 8. How to Compile

### Using GCC

Open a terminal in the project directory and run:

```bash
gcc main.c -o page_table_translator
```

Then run:

### Windows

```bash
page_table_translator.exe
```

### Linux / macOS

```bash
./page_table_translator
```

If your system uses another C compiler, the equivalent compile command can be used.

---

## 9. How to Use the Program

### Step 1: Start the program

The program first displays the project title.

### Step 2: Select the page size

Choose one of the available page-size options.

The selected page size is used throughout the current simulation.

### Step 3: Enter the number of frames

Enter a value between the allowed minimum and maximum.

### Step 4: Configure the page table

Enter:

1. Number of pages currently loaded
2. Page number
3. Frame number

The program checks that:

* The page number is valid.
* The frame number is valid.
* A page is not mapped twice.
* A frame is not assigned to two pages.
* The number of loaded pages does not exceed the available frames.

### Step 5: Use the Main Menu

The program then provides the following options:

```text
1. Display Page Table
2. Translate Address
3. New Simulation
4. Exit
```

### Step 6: Translate addresses

Select **Translate Address**.

The program asks how many logical addresses should be translated, with a maximum of 12 per run.

For each address, the program calculates the page number and offset, checks the page table, and either produces the physical address or reports a page fault.

---

## 10. Example Translation

Assume:

```text
Page Size = 1024 bytes
Logical Address = 2500
```

The page number is:

```text
2500 / 1024 = 2
```

The offset is:

```text
2500 % 1024 = 452
```

Therefore:

```text
Page Number = 2
Offset      = 452
```

If page 2 is mapped to frame 5:

```text
Physical Address
= Frame × Page Size + Offset
= 5 × 1024 + 452
= 5572
```

The program will display the translation as successful.

If page 2 is not mapped, the program instead reports:

```text
PAGE FAULT OCCURRED
```

No page replacement is performed.

---

## 11. Invalid Address Handling

The logical address space is limited by the configured number of pages and page size.

Therefore, an address outside the calculated logical address space is rejected as an invalid address.

For example, if:

```text
Number of Pages = 16
Page Size = 1024 bytes
```

the valid logical address range is:

```text
0 to 16383
```

An address of `16384` is therefore outside the logical address space and must be rejected rather than being treated as a page fault.

---

## 12. Testing

The program was tested using valid and invalid inputs covering the major functionality of the simulator.

Testing included:

* Valid page-size selection
* Invalid page-size selection
* Valid frame counts
* Frame counts below the minimum
* Frame counts above the maximum
* Valid page mappings
* Duplicate page mappings
* Duplicate frame mappings
* Invalid page numbers
* Invalid frame numbers
* Zero loaded pages
* Loaded pages exceeding available frames
* Valid logical addresses
* Negative logical addresses
* Addresses outside the logical address space
* Successful address translations
* Page fault situations
* Multiple address translations
* Maximum translation limit
* New simulation functionality
* Exit functionality
* Page table display

All major test cases were completed successfully after fixing the identified issues during testing.

---

## 13. Limitations

This project is a simplified simulation and does not attempt to reproduce the complete memory-management system of a real operating system.

For example:

* Only one-level paging is implemented.
* No page replacement algorithm is implemented.
* Pages are mapped manually by the user.
* The simulation does not manage real physical memory.
* Page faults are reported but do not trigger page loading.
* The program operates through a command-line interface.

These limitations are intentional and are consistent with the scope of the Page Table Translator requirement.

---

## 14. Future Improvements

Possible future improvements include:

* Adding a graphical user interface.
* Adding automatic page-table generation.
* Showing the address translation process step-by-step.
* Adding binary representation of logical and physical addresses.
* Adding translation history.
* Adding a visual memory-frame representation.
* Improving portability of console colours.
* Separating the implementation into multiple source and header files.

---

## 15. Author

**Safwan**

Operating Systems Mini Project
Group A – Page Table Translator

---

## 16. Academic Context

This project was developed as an Operating Systems mini project to practically demonstrate the basic concepts of paging, page tables, virtual memory, and logical-to-physical address translation.

The implementation prioritizes correctness, input validation, and clear console output while keeping the system simple enough to demonstrate the underlying Operating Systems concepts.

---

## 17. License

This project was developed for academic purposes.

# Page Table Translator

**EEI5265 - Operating Systems Mini Project**
**Group A - Page Table Translator**

A console-based C program that simulates the translation of logical addresses into physical addresses using a one-level page table.

---

## 1. Project Overview

The Page Table Translator is a simple simulation of how an operating system translates a logical address into a physical address using paging.

The program allows the user to:

* Select the page size at runtime.
* Select the number of physical frames.
* Create a page-to-frame mapping manually.
* View the current page table.
* Translate one or more logical addresses.
* Detect page faults when a page is not loaded.
* Reject logical addresses outside the valid address space.
* Start a new simulation without restarting the program.

The project focuses on demonstrating the basic concepts of:

* Logical addresses
* Physical addresses
* Pages
* Frames
* Page tables
* Offsets
* Page faults
* Address translation

---

## 2. Requirements

### Software

The program is written in **C** and requires a C compiler.

Recommended options include:

* GCC
* Code::Blocks with GCC
* Any IDE that supports standard C compilation

### Operating System

The program can be run from a Windows command prompt, terminal, or an IDE console that supports standard C input/output.

---

## 3. Project Constraints

The implementation follows the constraints given in the mini project specification.

| Requirement                  | Implementation               |
| ---------------------------- | ---------------------------- |
| Maximum pages                | 16                           |
| Maximum page size            | 1024 bytes (1 KB)            |
| Page sizes available         | 128, 256, 512 and 1024 bytes |
| Minimum frames               | 8                            |
| Maximum frames               | 16                           |
| Maximum translations per run | 12                           |
| Paging type                  | One-level paging             |
| Page replacement             | Not implemented              |
| Unloaded page                | Reported as a page fault     |

The available page sizes are powers of two and do not exceed the maximum permitted page size of 1024 bytes.

---

## 4. Main Concepts

### 4.1 Logical Address

A logical address is the address generated within the logical address space.

The program separates a logical address into:

```text
Page Number + Offset
```

The page number identifies which page contains the address, while the offset identifies the exact location within that page.

---

### 4.2 Page Number

The page number is calculated using integer division:

```text
Page Number = Logical Address / Page Size
```

For example, with a page size of 1024 bytes:

```text
Logical Address = 1500

Page Number = 1500 / 1024
            = 1
```

Therefore, address 1500 belongs to page 1.

---

### 4.3 Offset

The offset identifies the position of the address within its page.

It is calculated using the remainder operation:

```text
Offset = Logical Address % Page Size
```

For example:

```text
Logical Address = 1500
Page Size = 1024

Offset = 1500 % 1024
       = 476
```

---

### 4.4 Physical Address

Once the page number is obtained, the page table is used to find the corresponding physical frame.

The physical address is then calculated as:

```text
Physical Address = Frame Number × Page Size + Offset
```

For example:

```text
Page Number = 1
Frame Number = 5
Offset = 476
Page Size = 1024

Physical Address = 5 × 1024 + 476
                 = 5596
```

---

### 4.5 Page Fault

If a page is not currently loaded into physical memory, its page table entry is stored as:

```text
UNMAPPED
```

The program detects this condition and displays:

```text
PAGE FAULT OCCURRED
```

No physical address is generated for an unmapped page.

---

## 5. How the Program Works

The program follows this general sequence:

```text
Start Program
      |
      v
Select Page Size
      |
      v
Select Number of Frames
      |
      v
Create Page Table
      |
      v
Enter Page-to-Frame Mappings
      |
      v
Display Main Menu
      |
      +-----------------------------+
      |                             |
      v                             v
Display Page Table           Translate Address
                                    |
                                    v
                         Calculate Page Number
                                    |
                                    v
                            Calculate Offset
                                    |
                                    v
                          Check Page Table
                              /       \
                             /         \
                            v           v
                       Mapped       Unmapped
                          |             |
                          v             v
                 Calculate Physical   Page Fault
                     Address
```

---

## 6. Running the Program

### Option 1 - Using Code::Blocks

1. Open Code::Blocks.
2. Open the `main.c` source file.
3. Make sure the project is configured as a C project.
4. Build the program.
5. Run the program.
6. Follow the instructions displayed in the console.

---

### Option 2 - Using GCC

Open a terminal in the directory containing `main.c`.

Compile the program using:

```bash
gcc main.c -o page_table_translator
```

Run it using:

### Windows

```bash
page_table_translator.exe
```

### Linux/macOS

```bash
./page_table_translator
```

---

## 7. Using the Program

### Step 1 - Select Page Size

When the program starts, it asks the user to select a page size.

Available options are:

```text
1. 128 bytes
2. 256 bytes
3. 512 bytes
4. 1024 bytes
```

The selected value is used throughout the current simulation.

---

### Step 2 - Select Number of Frames

The user is asked to enter the number of physical frames.

The valid range is:

```text
8 - 16
```

For example:

```text
Enter the number of Frames : 8
```

---

### Step 3 - Create the Page Table

The user specifies how many pages are currently loaded.

The program then asks for:

```text
Page Number
Frame Number
```

for each mapping.

For example:

```text
Page 0 -> Frame 3
Page 1 -> Frame 5
Page 4 -> Frame 7
```

The program prevents:

* Invalid page numbers.
* Invalid frame numbers.
* Mapping the same page more than once.
* Assigning the same frame to multiple pages.
* Loading more pages than available frames.

---

## 8. Main Menu

After creating the page table, the following menu is available:

```text
1. Display Page Table
2. Translate Address
3. New Simulation
4. Exit
```

### Display Page Table

Displays all 16 page entries and their corresponding frame numbers.

An unloaded page is shown as:

```text
UNMAPPED
```

---

### Translate Address

The user first specifies how many logical addresses they want to translate.

The allowed range is:

```text
1 - 12
```

The user does **not** have to enter all 12 addresses.

For example, the user can choose:

```text
How many logical addresses do you want to translate? (1-12): 3
```

and then enter three addresses.

The program displays the translation result for each address.

---

### New Simulation

The current simulation is discarded and the user can configure a new:

* Page size
* Frame count
* Page table

This allows multiple simulations to be performed without restarting the program.

---

### Exit

Terminates the program and displays the exit message.

---

## 9. Address Validation

The program calculates the maximum logical address based on the selected page size and the maximum number of pages.

The maximum address space is:

```text
Maximum Address Space = Page Size × 16
```

Since addresses start from zero, the largest valid address is:

```text
(Page Size × 16) - 1
```

For example, when the page size is 1024 bytes:

```text
Maximum Address Space = 1024 × 16
                     = 16384 bytes

Largest Valid Address = 16383
```

Therefore:

```text
16383 -> Valid
16384 -> Out of Bounds
```

An address outside the valid range is rejected instead of being treated as a page fault.

---

## 10. Example Translation

Assume the following configuration:

```text
Page Size : 1024 bytes
Frame Count : 8

Page 0 -> Frame 3
Page 1 -> Frame 5
Page 4 -> Frame 7
```

Suppose the user enters:

```text
Logical Address : 1500
```

### Step 1 - Calculate Page Number

```text
1500 / 1024 = 1
```

Therefore:

```text
Page Number = 1
```

### Step 2 - Calculate Offset

```text
1500 % 1024 = 476
```

Therefore:

```text
Offset = 476
```

### Step 3 - Find Frame

The page table contains:

```text
Page 1 -> Frame 5
```

Therefore:

```text
Frame Number = 5
```

### Step 4 - Calculate Physical Address

```text
Physical Address
= 5 × 1024 + 476
= 5596
```

The program therefore reports a successful translation with physical address `5596`.

---

## 11. Page Fault Example

Suppose page 2 is not mapped:

```text
Page 2 -> UNMAPPED
```

If the user enters an address belonging to page 2, the program detects that the page is not loaded.

For example, with a page size of 1024:

```text
Logical Address = 2048
```

The calculation gives:

```text
Page Number = 2048 / 1024
            = 2
```

Since page 2 is unmapped, the program displays:

```text
PAGE FAULT OCCURRED
```

No physical address is calculated.

---

## 12. Error Handling

The program validates user input at several stages.

It handles:

* Non-numeric input.
* Invalid page-size selections.
* Invalid frame counts.
* Invalid page numbers.
* Invalid frame numbers.
* Duplicate page mappings.
* Duplicate frame mappings.
* Invalid logical addresses.
* Negative logical addresses.
* Logical addresses outside the available address space.
* Invalid translation counts.

The program repeatedly asks for valid input instead of terminating when an invalid value is entered.

---

## 13. Source Code Structure

The project is implemented in a single C source file:

```text
main.c
```

Important functions include:

| Function                    | Purpose                                    |
| --------------------------- | ------------------------------------------ |
| `main()`                    | Controls the overall program flow          |
| `getPageSize()`             | Gets the page size from the user           |
| `getFrameCount()`           | Gets and validates the frame count         |
| `createPageTable()`         | Creates the page-to-frame mappings         |
| `getValidPageNumber()`      | Validates page numbers                     |
| `getValidFrameNumber()`     | Validates frame numbers                    |
| `isFrameUsed()`             | Checks whether a frame is already assigned |
| `translateLogicalAddress()` | Performs address translation               |
| `calculatePageNumber()`     | Calculates the page number                 |
| `calculateOffset()`         | Calculates the offset                      |
| `getPhysicalAddress()`      | Calculates the physical address            |
| `isPageFault()`             | Checks whether a page is unmapped          |
| `displayPageTable()`        | Displays the current page table            |
| `displayOutput()`           | Displays translation results               |
| `getTranslationCount()`     | Gets the number of addresses to translate  |
| `displayMenu()`             | Displays the main menu                     |

---

## 14. Data Representation

The page table is represented using an integer array:

```c
int pageTable[MAX_PAGES];
```

Each array index represents a page number.

The value stored at that index represents the corresponding frame number.

For example:

```text
pageTable[0] = 3
pageTable[1] = 5
pageTable[2] = -1
```

represents:

```text
Page 0 -> Frame 3
Page 1 -> Frame 5
Page 2 -> Unmapped
```

The constant:

```c
#define UNMAPPED -1
```

is used to represent pages that are not currently loaded into physical memory.

---

## 15. Limitations

This project is intentionally a simplified simulation of virtual memory.

The program does not implement:

* Multi-level page tables.
* Page replacement algorithms.
* Disk or secondary-storage simulation.
* Actual hardware memory management.
* Real operating-system memory allocation.
* Dynamic page replacement after a page fault.

When a page is not loaded, the program only reports the page fault as required by the project specification.

---

## 16. Testing

The program was tested using:

* Valid and invalid page sizes.
* Minimum and maximum frame counts.
* Valid and invalid page numbers.
* Valid and invalid frame numbers.
* Duplicate page mappings.
* Duplicate frame mappings.
* Valid logical addresses.
* Negative addresses.
* Out-of-bounds addresses.
* Page-boundary addresses.
* Mapped pages.
* Unmapped pages.
* Different page sizes.
* Different translation counts.
* The maximum 12 translations per run.
* New simulation functionality.
* Program exit functionality.

Boundary tests were also performed to verify that the maximum valid logical address is accepted and the first address outside the address space is rejected.

---

## 17. Project Files

The implementation submission contains:

```text
main.c
README.md
```

`main.c` contains the complete implementation of the Page Table Translator.

The README provides the instructions and technical information required to compile and use the program.

---

## 18. Viva Demonstration

During the viva, the program can be demonstrated by following this sequence:

1. Start the program.
2. Select a page size.
3. Select the number of physical frames.
4. Create several page-to-frame mappings.
5. Display the page table.
6. Translate a valid logical address.
7. Translate an address belonging to an unmapped page to demonstrate a page fault.
8. Enter an out-of-bounds address to demonstrate validation.
9. Perform multiple translations in one run.
10. Start a new simulation if required.
11. Exit the program.

The main concepts that can be demonstrated during the viva are:

```text
Logical Address
       ↓
Page Number + Offset
       ↓
Page Table Lookup
       ↓
Frame Number
       ↓
Physical Address
```

---

## 19. Author

**Author:** Safwan
**Course:** EEI5265 - Operating Systems
**Project:** Mini Project - Group A: Page Table Translator
**Year:** 2026

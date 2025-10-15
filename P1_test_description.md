# 🎭 MCMT Ticket Program — Test Case Documentation

---

## **Test Case 1 — Matinee, Valid Inputs, No Seniors**

### **Scenario**
Entering all correct inputs and requesting accessible seats on a Saturday matinee with 0 senior tickets.

### **Input Summary**
```
S
M
3 0 1
Y
2
```

### **Expected Behavior**
✅ Program should complete successfully.

### **What to Validate in Output**
- Displays *Saturday Matinee* as performance.  
- Shows correct total of 4 tickets.  
- Accessible seat count (2) is valid (≤ half).  
- No discount applied.  
- Output formatted as a receipt with aligned decimals.

### **Correct Totals**
| Field | Amount |
|--------|---------|
| Subtotal | $96.88 |
| Discount | $0.00 |
| Final ticket price | $96.88 |
| Processing fees | $2.00 |
| **Final cost** | **$98.88** |

---

## **Test Case 2 — Evening, Valid Inputs, Accessible Seats**

### **Scenario**
Entering all correct inputs and requesting accessible seats for a Saturday evening show.

### **Input Summary**
```
S
E
2 1 1
Y
2
```

### **Expected Behavior**
✅ Program should complete successfully.

### **What to Validate in Output**
- Displays *Saturday Evening* as performance.  
- Uses evening ticket pricing.  
- Accessible seats valid (≤ half of total).  
- No discount.  
- Totals and formatting correct.

### **Correct Totals**
| Field | Amount |
|--------|---------|
| Subtotal | $125.96 |
| Discount | $0.00 |
| Final ticket price | $125.96 |
| Processing fees | $2.00 |
| **Final cost** | **$127.96** |

---

## **Test Case 3 — Invalid Day (“Tuesday”)**

### **Scenario**
Entering an invalid day input that does not start with F, S, or U.

### **Input Summary**
```
Tuesday
```

### **Expected Behavior**
❌ Program should terminate with an error.

### **What to Validate in Output**
- Only first character (`T`) used → invalid.  
- Displays descriptive error message about invalid day.  
- Program exits immediately (no further prompts).

### **Correct Totals**
_Not applicable (invalid input)._

---

## **Test Case 4 — Too Many Accessible Seats**

### **Scenario**
Requesting more accessible seats than allowed for a small group.

### **Input Summary**
```
F
3 1 0
Y
3
```

### **Expected Behavior**
❌ Program should terminate with an error.

### **What to Validate in Output**
- Friday evening automatically selected.  
- Total tickets = 4.  
- Accessible seat request (3) exceeds half of total.  
- Error message specifies max allowed (2).  
- Program ends without price summary.

### **Correct Totals**
_Not applicable (invalid input)._

---

## **Test Case 5 — Group Discount (>10 Tickets)**

### **Scenario**
Valid Sunday matinee order with group discount applied.

### **Input Summary**
```
U
5 5 2
N
```

### **Expected Behavior**
✅ Program should complete successfully with discount applied.

### **What to Validate in Output**
- Sunday matinee pricing used.  
- Group discount (7.5%) correctly calculated.  
- Discount line included in summary.  
- Final totals correctly computed and formatted.

### **Correct Totals**
| Field | Amount |
|--------|---------|
| Subtotal | $282.64 |
| Discount | $21.20 |
| Final ticket price | $261.44 |
| Processing fees | $6.00 |
| **Final cost** | **$267.44** |

---

## **Test Case 6 — Zero Tickets Entered**

### **Scenario**
User enters zero for all ticket counts.

### **Input Summary**
```
S
M
0 0 0
```

### **Expected Behavior**
❌ Program should terminate with an error.

### **What to Validate in Output**
- Detects total tickets = 0.  
- Displays appropriate error message.  
- Ends execution without calculating totals.

### **Correct Totals**
_Not applicable (invalid input)._

---

## **Test Case 7 — Skip Logic Check (No Time or Accessible Prompts)**

### **Scenario**
User chooses Friday and no accessible seats — program should skip irrelevant questions.

### **Input Summary**
```
F
2 1 0
N
```

### **Expected Behavior**
✅ Program should complete successfully.

### **What to Validate in Output**
- Does **not** ask for time (Friday auto evening).  
- Does **not** ask for accessible seats.  
- Displays Friday evening pricing.  
- Correct totals printed.

### **Correct Totals**
| Field | Amount |
|--------|---------|
| Subtotal | $135.96 |
| Discount | $0.00 |
| Final ticket price | $135.96 |
| Processing fees | $1.50 |
| **Final cost** | **$137.46** |

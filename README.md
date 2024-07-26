
##
# Vending Washing Machine


# 1. Project Overview
## Block diagram:
  ![vendingWashingBlock1](https://github.com/user-attachments/assets/4564eec6-aeea-43ba-8043-674b3de261c9)
  
##	Description: 
##	Objectives: 
-
-	
-	

# 2. System Architecture
##	Components:
-	Washing Machine
-	7 Seg Display 
-	Coin Selector
-	Button
-	Microcontroller
##	Communication Protocols:
-	
-	


# 3. Detailed Design
## 3.1 Washing Machine :
 - This acts as both input and output to uC. 
 - Based on Input coin value, the modes needs to selected
 - Possibility of 3 modes
  - * 15 Min [Coin value 1]
  - * 30 Min [Coin value 2]
  - * 45 Min [Coin value 3]
- Feedback on each state is needed
  - 1. Idle
  - 2. Running
  - 3. Done             



# 3.2 7 Seg Display :
 - On power on display based on current state 
 - Idle State
    * Display ‘rdy’
    * On coin insertion , display countdown timer of 20 sec
  - Running state 
    * Display countdown timer based on mode selected
    *  
- Done state
  * Display ‘ovr’ for ~10 sec and then change to ‘rdy’
- Reset state
  * Only used by machine owners
  * On long press display total coin collected values ‘val ’ / ‘000’ , alternately
  * On press single click value reset to zero , display ‘000’ for 3 sec and change to ‘rdy’      


# 3.3 Coin Selector:
- It gives the impluses based on the types of coin
- Currently we are sticking to 1 value of coin i.e 1 Dhiram
- It gives if a coin is valid
- In case of valid value is set to 1 
- In case of invalid coin is rejected

# 3.4 Button:
- Not exposed to normal users, only for machine owners
- Press long ~5 sec to display total collected coin value
- Then a single press to reset the value

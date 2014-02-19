(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) -10)
         (= (citythreat city2) 500)
         (= (citythreat city3) 490)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 490)
         (= (timeTerre city1 city0) 490)
         (= (timeTerre city4 city1) 490)
         (= (timeTerre city1 city4) 490)
         
; city2
         (= (timeTerre city0 city2) 500)
         (= (timeTerre city2 city0) 500)
         (= (timeTerre city4 city2) 500)
         (= (timeTerre city2 city4) 500)
         
; city3
         (= (timeTerre city0 city3) -10)
         (= (timeTerre city3 city0) -10)
         (= (timeTerre city4 city3) -10)
         (= (timeTerre city3 city4) -10)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (libre plane1)
         (libre plane2)
         
; person init
         (at person1 city0)
         (at person2 city0)
         (at person3 city0)
         (at person4 city0)
         (at person5 city0)
         (at person6 city0)
         
)
(:goal (and 
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         (at person4 city4)
         (at person5 city4)
         (at person6 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 4900 -100
; 4880 400
; 3900 900
; 3860 1400
; 2900 1900
; 2840 2400
; 1900 2900
; 1820 3400
; 900 3900
; 820 4400
; -100 4900

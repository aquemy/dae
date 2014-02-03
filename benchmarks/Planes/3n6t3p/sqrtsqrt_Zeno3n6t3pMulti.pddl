(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1.5)
         (= (citythreat city2) 2.32843)
         (= (citythreat city3) 2.9641)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 2.9641)
         (= (timeTerre city1 city0) 2.9641)
         (= (timeTerre city4 city1) 2.9641)
         (= (timeTerre city1 city4) 2.9641)
         
; city2
         (= (timeTerre city0 city2) 2.32843)
         (= (timeTerre city2 city0) 2.32843)
         (= (timeTerre city4 city2) 2.32843)
         (= (timeTerre city2 city4) 2.32843)
         
; city3
         (= (timeTerre city0 city3) 1.5)
         (= (timeTerre city3 city0) 1.5)
         (= (timeTerre city4 city3) 1.5)
         (= (timeTerre city3 city4) 1.5)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (at plane3 city0)
         (libre plane1)
         (libre plane2)
         (libre plane3)
         
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
; 17.7846 13.5
; 16.5133 15.9853
; 14.8564 17.8923
; 13.5851 20.3776
; 11.9282 22.2846
; 10.6569 24.7699
; 9 26.6769

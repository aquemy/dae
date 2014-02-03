(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1)
         (= (citythreat city2) 2.38629)
         (= (citythreat city3) 3.19722)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 3.19722)
         (= (timeTerre city1 city0) 3.19722)
         (= (timeTerre city4 city1) 3.19722)
         (= (timeTerre city1 city4) 3.19722)
         
; city2
         (= (timeTerre city0 city2) 2.38629)
         (= (timeTerre city2 city0) 2.38629)
         (= (timeTerre city4 city2) 2.38629)
         (= (timeTerre city2 city4) 2.38629)
         
; city3
         (= (timeTerre city0 city3) 1)
         (= (timeTerre city3 city0) 1)
         (= (timeTerre city4 city3) 1)
         (= (timeTerre city3 city4) 1)
         
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
; 31.9722 10
; 30.3504 12.7726
; 27.5778 14.3944
; 25.9559 17.167
; 23.1833 18.7889
; 21.5615 21.5615
; 18.7889 23.1833
; 17.167 25.9559
; 14.3944 27.5778
; 12.7726 30.3504
; 10 31.9722

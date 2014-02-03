(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 14.1421)
         (= (citythreat city2) 100.995)
         (= (citythreat city3) 142.127)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 142.127)
         (= (timeTerre city1 city0) 142.127)
         (= (timeTerre city4 city1) 142.127)
         (= (timeTerre city1 city4) 142.127)
         
; city2
         (= (timeTerre city0 city2) 100.995)
         (= (timeTerre city2 city0) 100.995)
         (= (timeTerre city4 city2) 100.995)
         (= (timeTerre city2 city4) 100.995)
         
; city3
         (= (timeTerre city0 city3) 14.1421)
         (= (timeTerre city3 city0) 14.1421)
         (= (timeTerre city4 city3) 14.1421)
         (= (timeTerre city3 city4) 14.1421)
         
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
; 852.76 127.279
; 770.497 387.838
; 596.791 511.233
; 568.507 684.939
; 514.528 771.792
; 486.244 854.055
; 340.822 895.187
; 286.843 1068.89
; 284.253 1151.16
; 258.559 1155.75
; 201.99 1238.01
; 84.8528 1279.14

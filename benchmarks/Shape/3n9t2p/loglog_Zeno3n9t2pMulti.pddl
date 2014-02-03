(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 - person
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
         (at person7 city0)
         (at person8 city0)
         (at person9 city0)
         
)
(:goal (and 
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         (at person4 city4)
         (at person5 city4)
         (at person6 city4)
         (at person7 city4)
         (at person8 city4)
         (at person9 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 51.1556 16
; 49.5337 18.7726
; 46.7611 20.3944
; 45.1393 23.167
; 42.3667 24.7889
; 40.7448 27.5615
; 37.9722 29.1833
; 36.3504 31.9559
; 33.5778 33.5778
; 31.9559 36.3504
; 31.9559 36.3504
; 29.1833 37.9722
; 27.5615 40.7448
; 24.7889 42.3667
; 23.167 45.1393
; 20.3944 46.7611
; 18.7726 49.5337
; 16 51.1556

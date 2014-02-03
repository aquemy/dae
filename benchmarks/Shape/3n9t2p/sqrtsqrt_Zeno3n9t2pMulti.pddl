(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 person7 person8 person9 - person
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
; 47.4256 24
; 46.1543 25.6569
; 44.4974 26.9282
; 43.2261 28.5851
; 41.5692 29.8564
; 40.2979 31.5133
; 38.641 32.7846
; 37.3697 34.4415
; 35.7128 35.7128
; 35.7128 35.7128
; 34.4415 37.3697
; 32.7846 38.641
; 31.5133 40.2979
; 29.8564 41.5692
; 28.5851 43.2261
; 28.5851 43.2261
; 26.9282 44.4974
; 25.6569 46.1543
; 24 47.4256

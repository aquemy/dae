(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 69)
         (= (citythreat city2) 109)
         (= (citythreat city3) 138)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 138)
         (= (timeTerre city1 city0) 138)
         (= (timeTerre city4 city1) 138)
         (= (timeTerre city1 city4) 138)
         
; city2
         (= (timeTerre city0 city2) 109)
         (= (timeTerre city2 city0) 109)
         (= (timeTerre city4 city2) 109)
         (= (timeTerre city2 city4) 109)
         
; city3
         (= (timeTerre city0 city3) 69)
         (= (timeTerre city3 city0) 69)
         (= (timeTerre city4 city3) 69)
         (= (timeTerre city3 city4) 69)
         
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
; 1380 690
; 1322 770
; 1242 828
; 1184 908
; 1104 966
; 1046 1046
; 966 1104
; 908 1184
; 828 1242
; 770 1322
; 690 1380

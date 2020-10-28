(ns goedel
  (:require [clojure.math.numeric-tower :as math]))

(def dictionary_az [{:char \a :num 1} {:char \b :num 2} {:char \c :num 3} {:char \d :num 4} {:char \e :num 5} {:char \f :num 6}
    {:char \g :num 7} {:char \h :num 8} {:char \i :num 9} {:char \j :num 10} {:char \k :num 11} {:char \l :num 12}
    {:char \m :num 13} {:char \n :num 14} {:char \o :num 15} {:char \p :num 16} {:char \q :num 17} {:char \r :num 18}
    {:char \s :num 19} {:char \t :num 20} {:char \u :num 21} {:char \v :num 22} {:char \w :num 23} {:char \x :num 24}
    {:char \y :num 25} {:char \z :num 26}])

(def dictionary_az_AZ [{:char \a :num 1} {:char \b :num 2} {:char \c :num 3} {:char \d :num 4} {:char \e :num 5} {:char \f :num 6}
    {:char \g :num 7} {:char \h :num 8} {:char \i :num 9} {:char \j :num 10} {:char \k :num 11} {:char \l :num 12}
    {:char \m :num 13} {:char \n :num 14} {:char \o :num 15} {:char \p :num 16} {:char \q :num 17} {:char \r :num 18}
    {:char \s :num 19} {:char \t :num 20} {:char \u :num 21} {:char \v :num 22} {:char \w :num 23} {:char \x :num 24}
    {:char \y :num 25} {:char \z :num 26} {:char \A :num 27} {:char \B :num 28} {:char \C :num 29} {:char \D :num 30}
    {:char \E :num 31} {:char \F :num 32} {:char \G :num 33} {:char \H :num 34} {:char \I :num 35} {:char \J :num 36}
    {:char \K :num 37} {:char \L :num 38} {:char \M :num 39} {:char \N :num 40} {:char \O :num 41} {:char \P :num 42}
    {:char \Q :num 43} {:char \R :num 44} {:char \S :num 45} {:char \T :num 46} {:char \U :num 47} {:char \V :num 48}
    {:char \W :num 49} {:char \X :num 50} {:char \Y :num 51} {:char \Z :num 52}])


(defn getFirstLabelEq
  [mapColl target label]
  (first (filter #(= target (get %1 label)) mapColl)))

(defn charToNum 
  [dict char]
  (if-let [num (get (getFirstLabelEq dict char :char) :num)]
    num
    0))

(charToNum dictionary_az \h)
(charToNum dictionary_az_AZ \F)
(charToNum [] \a)
(charToNum dictionary_az_AZ \%)

(defn numToChar
  [dict num]
  (if-let [char (get (getFirstLabelEq dict num :num) :char)]
    char
    \*))

(numToChar [] 42)
(numToChar dictionary_az 42)
(numToChar dictionary_az 13)
(numToChar dictionary_az_AZ 42)


(defn translate
  [dict string]
  (map #(charToNum dict %1) string))

(translate dictionary_az "goedel")
(translate dictionary_az_AZ "Goedel")
(translate dictionary_az_AZ "GOEDEL")
(translate dictionary_az_AZ "!GOEDEL!")
(translate dictionary_az_AZ "")

(defn divides? [m n] (zero? (rem m n)))
(defn prime? [n] (and (< 1 n) (not-any? #(divides? n %) (range 2 n))))

(def primeList (filter prime? (iterate inc 2)))

(defn encode
  [dict string]
  (reduce * (map #(math/expt %1 %2) primeList (translate dict string))))

(encode dictionary_az "abba")
(encode dictionary_az "Abba")
(encode dictionary_az_AZ "Abba")
(encode [] "abba")
(encode dictionary_az "")

(defn primeFactors [a]
  (let [pfRec (fn [n factors primes]
    (if (<= n 1)
      factors
      (if (divides? n (first primes))
        (recur (/ n (first primes)) (conj factors (first primes)) primes)
        (recur n factors (next primes)))))]
    (pfRec a [] primeList)))

(primeFactors 1)
(primeFactors 42)
(primeFactors 661)
(primeFactors 144)

(defn id [x] x)

(defn decode [dict num]
  (->> (primeFactors num)
       (partition-by identity)
       (map count)
       (map #(numToChar dict %))
       (apply str)))

(decode dictionary_az 1575)
(decode dictionary_az_AZ 1575)
(decode dictionary_az 211392921600)
(decode dictionary_az_AZ 211392921600)
(decode dictionary_az 3150)
(decode dictionary_az 661)
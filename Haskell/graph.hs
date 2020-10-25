{-# LANGUAGE LambdaCase #-}
module Graph where

import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.Map (Map)
import Data.Set (Set)

task1 :: Ord a => [(a, [a])] -> Map a (Set a)
task1 = foldr (\(a, as) m -> (\m2 -> foldr (\a2 -> Map.insertWith Set.union a2 (Set.singleton a)) m2 $ filter (Map.notMember m) as) $ Map.insertWith Set.union a (Set.fromList $ filter (Map.notMember m) as) m) Map.empty

task2 :: Ord a => Map a (Set a) -> a -> a -> [a]
task2 graph a b = head $ until (any (elem b)) (\xxs -> filter (\case {(p:_:q:_) -> p /= q ; [] -> False; _ -> True}) $ [ x:xs | xs <- xxs, x <- maybe [] Set.toList (Map.lookup (head xs) graph) ]) [[a]]
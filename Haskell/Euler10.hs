module Euler10 where
import Control.Monad (forM_, when)

import Control.Monad.ST
import Data.Array.ST
import Data.Array.Unboxed

sieve :: Int -> UArray Int Bool
sieve n = runSTUArray $ do
    let m = (n-1) `div` 2
        r = floor . sqrt $ fromIntegral n
    bits <- newArray (0, m-1) True
    forM_ [0 .. r `div` 2 - 1] $ \i -> do
        isPrime <- readArray bits i
        when isPrime $ do
            forM_ [2*i*i+6*i+3, 2*i*i+8*i+6 .. (m-1)] $ \j -> do
                writeArray bits j False
    return bits

primes :: Int -> [Int]
primes n = 2 : [2*i+3 | (i, True) <- assocs $ sieve n]

result = sum $ primes 2000000
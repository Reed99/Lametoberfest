{-# LANGUAGE OverloadedStrings #-}

module JSON where

import Data.Aeson
import Control.Applicative
import Data.ByteString.Lazy.Char8 hiding (empty)

data MyData = MyData { text :: String, number :: Int } deriving Show

instance ToJSON MyData where
    toJSON (MyData text number) = object ["text" .= text, "number" .= number]

instance FromJSON MyData where
    parseJSON (Object v) = MyData <$> v .: "text" <*> v .: "number"
    parseJSON _          = empty

myData = MyData "Hello" 123

main = do
    print myData
    print $ unpack $ encode myData
    print $ (decode "{ \"number\" : 123, \"text\" : \"Hello\" }" :: Maybe MyData)
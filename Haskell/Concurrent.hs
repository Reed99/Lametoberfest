import Control.Concurrent.STM

type Account = TVar Integer

credit account amount = do
    current <- readTVar account
    writeTVar account (current + amount)

debit account amount = do
    current <- readTVar account
    writeTVar account (current - amount)

transfer from to amount =
    atomically $ do
        debit from amount
        credit to amount

main = do
    account1 <- atomically $ newTVar 10
    account2 <- atomically $ newTVar 20

    transfer account1 account2 5

    balance1 <- atomically $ readTVar account1
    balance2 <- atomically $ readTVar account2
    print balance1
    print balance2
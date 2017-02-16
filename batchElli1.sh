# Parallelization Script
# July 13, 2016

LPERSISTENCEITIM=0.1

mkdir ITIMLocationChecklPersistenceITIM

TOTALITERATIONS=1

for LPERSISTENCEITIM in `seq 0.1 0.1 2`
do

echo "LPERSISTENCEITIM = $LPERSISTENCEITIM"

NRequested=`ps | grep -c elli1`

ITERATIONS=1

while (( $ITERATIONS <= $TOTALITERATIONS ))
    do

    # loop to periodically check how many runs are submitted

    while (( $NRequested >= $1 ))   # while number requested is greater than number of processors we want to use (user input in command line)

        do
            sleep 1     # wait 1 sec before checking again

            NRequested=`ps | grep -c elli1` # check again

    done

        echo "Done sleeping."

    # loop to submit more runs until reach max number of processors we want to use ($1)

    while (( $NRequested < $1 && $ITERATIONS <= $TOTALITERATIONS ))
        do

            # run program with specified parameters

            ./elli1.x params.txt ITIMLocationCheck.lPersistenceITIM.$LPERSISTENCEITIM 1 -1 -1 $LPERSISTENCEITIM &

            # If user gives V or v as second command line argument, then code will be verbose. Any other input will result in non-verbose.
            if [[ $2 == "V" || $2 == "v" ]]
                then
                    # print to screen the process ID and the name of the run
                    echo "PID of Elli1.$LPERSISTENCEITIM is $!"
            fi

            # update number of running programs
            NRequested=`ps | grep -c elli1`

            # increase iteration run by 1
            ITERATIONS=$(( ITERATIONS + 1 ))
    done
            echo "Done calling elli1."
done

done

# wait for all background processes to finish before concatenating files
wait

echo "Done waiting for processes to finish."

mv ITIMLocationCheck.lPersistenceITIM.* ~/Documents/SPR-SHP1Occlusion/elli3/src/ITIMLocationChecklPersistenceITIM




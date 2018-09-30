#/bin/bash
. vpl_environment.sh
ls 
unzip *.zip > /dev/null 
orig_dir=$(pwd)
first_par=${VPL_SUBFILE0%.*}
cd $first_par
ls
printf "\n===============================================\n"
printf "1. Checking writeup.txt\n"
printf "===============================================\n"
if python $orig_dir/writeup_checker.py $orig_dir/writeup.txt; then
    printf "Proceeding for further checks.\n"
else 
    printf "Not proceeding for further checks\n"
    exit 0
fi
file_arr=(test)
# file_arr=(inputfile1 inputfile2 inputfile3)
printf "\n===============================================\n"
printf "2. Running ${orig_dir}/compile.sh : \n"
printf "===============================================\n"
chmod +x ${orig_dir}/compile.sh
chmod +x ./minisat_114
if timeout 30s ${orig_dir}/compile.sh; then
    printf "\n"
    echo "Runnning against input files"
    chmod +x ${orig_dir}/run1.sh
    for input_file in ${file_arr[@]};
    do
        # Execute run1.sh
        printf "\n===============================================\n"
        printf "3. Running run1.sh\n"
        printf "===============================================\n"
        execution=$(timeout 10s ${orig_dir}/run1.sh $orig_dir/${input_file} 2>&1) # equivalent to 0.1 mins time limit in input files
        
        exit_status=$?
        if [ $exit_status -eq 124 ] #timeout occured
        then
            printf "Execution Timeout (>10 sec) while evaluating $input_file\n\n"
            printf "Inputfile was \n"
            cat $orig_dir/${input_file}.graph
    
        elif [ $exit_status -eq 0 ] #No runtime error occured (Correct or wrong answer)
        then
            # ==========================================
            # Execute minisat.sh
            # ==========================================
            printf "Successful execution of run1.sh for $input_file :\n"
            printf "$execution\n\n"
            
            printf "\n===============================================\n"
            printf "4. Running minisat\n"
            printf "===============================================\n"
            
            execution_2=$(timeout 20s minisat $orig_dir/${input_file}.satinput $orig_dir/${input_file}.satoutput 2>&1) # equivalent to 0.1 mins time limit in input files
            exit_status_2=$?
            
            if [ $exit_status_2 -eq 124 ] #timeout occured
            then
                printf "Execution Timeout (>20 sec) while running minisat\n\n"
                printf "Inputfile was \n"
                cat $orig_dir/${input_file}.graph
            
            elif [ $exit_status_2 -eq 3 ] #No runtime error occured (Correct or wrong answer)
            then
                printf "Incorrect format of clauses to minisat\n\n"
                printf "Test Inputfile was \n"
                cat $orig_dir/${input_file}.graph
            
            elif [ $exit_status_2 -eq 10 -o $exit_status_2 -eq 20 ] #No runtime error occured (Correct or wrong answer)
            then
                # Execute minisat.sh
                printf "Successful execution of minisat for $input_file :\n"
                printf "$execution_2\n\n"
                
                printf "\n\n===============================================\n"
                printf "5. Running run2.sh\n"
                printf "===============================================\n"
                # ==========================================
                # Execute run2.sh
                # ==========================================
                execution_3=$(timeout 10s ${orig_dir}/run2.sh $orig_dir/${input_file} 2>&1) # equivalent to 0.1 mins time limit in input files

                exit_status_3=$?

                if [ $exit_status_3 -eq 124 ] #timeout occured
                then
                    printf "Execution Timeout (>10 sec) while running run2.sh\n\n"
                    printf "Inputfile was \n"
                    cat $orig_dir/${input_file}.graph
                
                elif [ $exit_status_3 -eq 0 ] #No runtime error occured (Correct or wrong answer)
                then
                    printf "$execution_3\n\n"


                    printf "\n\n===============================================\n"
                    printf "6. Checking final OP format\n"
                    printf "===============================================\n"
                    execution_4=$(python $orig_dir/checker.py $orig_dir/${input_file}.graph $orig_dir/${input_file}.subgraphs 2>&1) # equivalent to 0.1 mins time limit in input files

                    exit_status_4=$?

                    # if [ $exit_status_4 -eq 124 ] #timeout occured
                    # then
                    #     printf "Execution Timeout (>10 sec) while running run2.sh\n\n"
                    #     printf "Inputfile was \n"
                    #     cat $orig_dir/${input_file}.graph
                    
                    if [ $exit_status_4 -eq 0 ] #No runtime error occured (Correct or wrong answer)
                    then
                        printf "$execution_4\n\n"
                        printf "\n===============================================\n"
                        printf "7. Successful Execution of everything\n\n"
                        printf "Note that this is just for format checking and not for evaluation "
                        printf "\n===============================================\n"
                    else #some error occured for this test case
                        printf "Runtime Error (in OP checker): $execution_4\n\n"
                        printf "Input file was \n"
                        cat $orig_dir/${input_file}.graph
                    fi

                else #some error occured for this test case
                    printf "Runtime Error (in run2.sh): $execution_3\n\n"
                    printf "Input file was \n"
                    cat $orig_dir/${input_file}.graph
                fi

            else #some error occured for this test case
                printf "Runtime Error (in minisat): $execution_2\n\n"
                printf "Input file was \n"
                cat $orig_dir/${input_file}.graph
            fi

        else #some error occured for this test case
            printf "Runtime Error: $execution\n\n"
            printf "Input file was \n"
            cat $orig_dir/${input_file}.graph
        fi
    done

else
    echo "compilation failed/timed out"
fi
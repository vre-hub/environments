FROM rootproject/root:6.24.06-ubuntu20.04
USER root
ADD . /code
WORKDIR /code
# adding group right to write to  repo
RUN chmod -R g+w /code 
# RUN chown -R root /code
RUN bash -c 'echo "Start electron channel recast test" && \
    ln -s recast/test/ntuples/ ./ && \
    python3 runSelector.py --data mc16a --bkgs recast --doSyst 1 --doTruth 1 && \
    python3 runSelector.py --data mc16d --bkgs recast --doSyst 1 --doTruth 1 && \
    python3 runSelector.py --data mc16e --bkgs recast --doSyst 1 --doTruth 1 && \
    echo "Run recast/MakeSignalInfo.py" && \
    python3 recast/MakeSignalInfo.py && \
    echo "Prepare signal template file for METsig bin 1 for channel ee" && \
    python3 recast/InputMaker.py --chn ee --cut SR_bin1_METsig --doSyst 1 && \
    echo "Prepare signal template file for METsig bin 2 for channel ee" && \
    python3 recast/InputMaker.py --chn ee --cut SR_bin2_METsig --doSyst 1 && \
    echo "Prepare signal template file for METsig bin 3 for channel ee" && \
    python3 recast/InputMaker.py --chn ee --cut SR_bin3_METsig --doSyst 1 && \
    echo "Cleaning up" && \
    rm ntuples && \
    rm Signal_info* && \
    rm signal_templates* && \
    rm -r Histograms && \
    echo "time stamp: $(date)" > /code/build.stamp'

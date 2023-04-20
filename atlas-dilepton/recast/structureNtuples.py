import os;

os.mkdir('ntuples/mc16a');
os.mkdir('ntuples/mc16d');
os.mkdir('ntuples/mc16e');

for f in os.listdir('ntuples'):

    if not '.root' in f: continue;
    
    camp = '';
    if 'r9364' in f:
        camp = 'mc16a';
    elif 'r10201' in f:
        camp = 'mc16d';
    elif 'r10724' in f:
        camp = 'mc16e';
    else:
        print( 'ERROR: did not recognize mc campaign from r-tag' );

    name = f.split('.deriv')[0] + '_minitrees.root';

    os.mkdir('ntuples/'+camp+'/user.dummy.recastSignal.'+name);
    cmd = 'mv ntuples/'+f+' ntuples/'+camp+'/user.dummy.recastSignal.'+name+'/user.dummy.dummy._000001.minitrees.root';
    print( cmd );
    os.system(cmd);

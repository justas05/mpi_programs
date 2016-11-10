#!/bin/bash
export HISTCONTROL="ignoreboth"
export HISTSIZE="1000"
export HOME="/home/S12307"
export HOSTNAME="head.cluster.local"
export LANG="ru_RU.UTF-8"
export LD_LIBRARY_PATH="/common/boost/lib:\$LD_LIBRARY_PATH"
export LESSOPEN="||/usr/bin/lesspipe.sh %s"
export LOGNAME="s12307"
export LS_COLORS="rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.axv=01;35:*.anx=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.axa=00;36:*.oga=00;36:*.spx=00;36:*.xspf=00;36:"
export MAIL="/var/spool/mail/s12307"
export OLDPWD
export PATH="/usr/runmvs/bin:/common/runmvs/bin:/common/runmvs/sbin:/common/mpich/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin"
export PWD="/home/S12307/mpi_programs/lab4"
export SHELL="/bin/bash"
export SHLVL="2"
export SSH_CLIENT="192.168.64.163 49768 22"
export SSH_CONNECTION="192.168.64.163 49768 192.168.64.197 22"
export SSH_TTY="/dev/pts/13"
export TERM="xterm"
export USER="s12307"
export XDG_RUNTIME_DIR="/run/user/12307"
export XDG_SESSION_ID="71"
EnvCommandLine=(
)
num_nodes=1
hosts_list="$2"
exitstatus_file="$3"
prefix="$5"
task_image="$4"
np=6
tview_flag=
progname="$5 /home/S12307/mpi_programs/lab4/./main"
mpich_args=""
cmdLineArgs=" -R"
width_distribution=0
numofnodes=1
proc_per_node=


MPIRUN_HOME=/common/mpich/bin
cd "/home/S12307/mpi_programs/lab4"

if [  "" ] ;then
  machine_file=`mktemp /tmp/machinefile.XXXXXX` || exit 1
  /common/runmvs/bin/confread $task_image Machinefile > $machine_file 
  gentmpname=`mktemp /tmp/machines.XXXXXX` || exit 1
  /common/runmvs/bin/genmachinefile "$hosts_list" $machine_file 6 >$gentmpname
  hosts_list=$gentmpname
  rm -f $machine_file
fi

trap ' if [ "" ] ; then   rm $gentmpname ;fi ; exit '  1 2 3 15



EnvCommandLine=(  "${EnvCommandLine[@]}" MACHINEFILE_NAME=$hosts_list ) 
    export LMUTIL=lmutil


if [ x = x-totalview ]
then
    if ! check_license -c /common/totalview/license.dat -f TV/Base
    then
        sleep 1
        echo 215 >$exitstatus_file
        exit 215
    fi
fi
(

. /common/runmvs/bin/run-mpich

)
exitstatus=$?

if [ 0 -ne 0 ] ; then
    exitstatus=215
fi


if [ "" ] ; then   rm $gentmpname ;fi 
echo $exitstatus >$exitstatus_file
exit $exitstatus

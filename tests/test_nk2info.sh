#!/bin/bash
#
# nk2info tool testing script
#
# Copyright (c) 2009-2013, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

list_contains()
{
	LIST=$1;
	SEARCH=$2;

	for LINE in $LIST;
	do
		if test $LINE = $SEARCH;
		then
			return ${EXIT_SUCCESS};
		fi
	done

	return ${EXIT_FAILURE};
}

test_info()
{ 
	DIRNAME=$1;
	INPUT_FILE=$2;
	BASENAME=`basename ${INPUT_FILE}`;

	rm -rf tmp;
	mkdir tmp;

	${TEST_RUNNER} ${NK2INFO} ${INPUT_FILE} | sed '1,2d' > tmp/${BASENAME}.log;

	RESULT=$?;

	if test -f "input/.nk2info/${DIRNAME}/${BASENAME}.log.gz";
	then
		zdiff "input/.nk2info/${DIRNAME}/${BASENAME}.log.gz" "tmp/${BASENAME}.log";

		RESULT=$?;
	else
		mv "tmp/${BASENAME}.log" "input/.nk2info/${DIRNAME}";

		gzip "input/.nk2info/${DIRNAME}/${BASENAME}.log";
	fi

	rm -rf tmp;

	echo -n "Testing nk2info of input: ${INPUT_FILE} ";

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

NK2INFO="../nk2tools/nk2info";

if ! test -x ${NK2INFO};
then
	NK2INFO="../nk2tools/nk2info.exe";
fi

if ! test -x ${NK2INFO};
then
	echo "Missing executable: ${NK2INFO}";

	exit ${EXIT_FAILURE};
fi

TEST_RUNNER="tests/test_runner.sh";

if ! test -x ${TEST_RUNNER};
then
	TEST_RUNNER="./test_runner.sh";
fi

if ! test -x ${TEST_RUNNER};
then
	echo "Missing test runner: ${TEST_RUNNER}";

	exit ${EXIT_FAILURE};
fi

if ! test -d "input";
then
	echo "No input directory found.";

	exit ${EXIT_IGNORE};
fi

OLDIFS=${IFS};
IFS="
";

RESULT=`ls input/* | tr ' ' '\n' | wc -l`;

if test ${RESULT} -eq 0;
then
	echo "No files or directories found in the input directory.";

	EXIT_RESULT=${EXIT_IGNORE};
else
	IGNORELIST="";

	if ! test -d "input/.nk2info";
	then
		mkdir "input/.nk2info";
	fi
	if test -f "input/.nk2info/ignore";
	then
		IGNORELIST=`cat input/.nk2info/ignore | sed '/^#/d'`;
	fi
	for TESTDIR in input/*;
	do
		if test -d "${TESTDIR}";
		then
			DIRNAME=`basename ${TESTDIR}`;

			if ! list_contains "${IGNORELIST}" "${DIRNAME}";
			then
				if ! test -d "input/.nk2info/${DIRNAME}";
				then
					mkdir "input/.nk2info/${DIRNAME}";
				fi
				if test -f "input/.nk2info/${DIRNAME}/files";
				then
					TESTFILES=`cat input/.nk2info/${DIRNAME}/files | sed "s?^?${TESTDIR}/?"`;
				else
					TESTFILES=`ls ${TESTDIR}/*`;
				fi
				for TESTFILE in ${TESTFILES};
				do
					if ! test_info "${DIRNAME}" "${TESTFILE}";
					then
						exit ${EXIT_FAILURE};
					fi
				done
			fi
		fi
	done

	EXIT_RESULT=${EXIT_SUCCESS};
fi

IFS=${OLDIFS};

exit ${EXIT_RESULT};


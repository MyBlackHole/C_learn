# cve-2014-0050
CVE-2014-0050 Vulnerable site sample

This project aims to demonstrate the CVE-2014-0050 exploitation for educational purpose.
For more informations, see :
* [https://www.trustwave.com/Resources/SpiderLabs-Blog/CVE-2014-0050--Exploit-with-Boundaries,-Loops-without-Boundaries/](https://www.trustwave.com/Resources/SpiderLabs-Blog/CVE-2014-0050--Exploit-with-Boundaries,-Loops-without-Boundaries/)
* [https://github.com/rapid7/metasploit-framework/blob/master/modules/auxiliary/dos/http/apache_commons_fileupload_dos.rb](https://github.com/rapid7/metasploit-framework/blob/master/modules/auxiliary/dos/http/apache_commons_fileupload_dos.rb)

## Legal Disclaimer

This project is made for educational and ethical testing purposes only. Attacking targets without prior mutual consent is illegal. It is the end user's responsibility to obey all applicable local, state and federal laws. Developers assume no liability and are not responsible for any misuse or damage caused by this program.

## Getting started

1. Start the docker container :

`docker run -d -p 8080:8080 jrrdev/cve-2014-0050:latest`

2. Download the exploit script on the attacker machine [here](https://github.com/jrrdev/cve-2014-0050/blob/master/exploit/exploit.py)

3. Run the python exploit script from the attacker machine :

`python exploit.py http://<DOCKER_HOST>:8080/hello`

4. Monitor CPU usage :-)

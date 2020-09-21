# Email Sniffer
A compact, simple email text NLP spider that extracts and preprocess email text for data mining, part of an ML project to predict and prevent fraud emails.

# Author
Wei Guo wei.parker.guo.sg@gmail.com

# Usage
This application is built by visual studio visual c++. You need c++ boost lib for it to compile. The upcoming frontend (not for current version) is planned to be written and run with Ultralight HTML Engine and should be platform independant as long as you have the right release version.

## Setup (for devs)
1. Navigate to your cloned repository.
2. Open EmailSniffer.sln using Visual Studio 2019.
3. Link with <a href="https://www.boost.org/">C++ Boost Lib</a>
4. Build and run under Release x64, Debug version will report assertion errors.

## Run (for all)
1. Execute EmailSniffer.exe
2. Type input as prompted. The working directory will be the root directory of the git repo.
3. Retrieve the csv you specified to be output and proceed to data mining softwares.

# Reference
Referenced code are commented with sources inline. Some of the extra modules are listed here:
<ul>
<li> Boost C++ Lib <a href="https://www.boost.org/">https://www.boost.org/</a></li>
<li> Ultralight HTML Engine <a href="https://github.com/ultralight-ux/Ultralight-API">https://github.com/ultralight-ux/Ultralight-API</a></li>
<li> Cornell SMART Stop Words List 2 <a href="http://www.lextek.com/manuals/onix/stopwords2.html">http://www.lextek.com/manuals/onix/stopwords2.html</a></li>
</ul>
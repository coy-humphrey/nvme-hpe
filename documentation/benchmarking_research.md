# Benchmarking Test and Framework Design Doc

## Use Cases

## Existing Frameworks

While there are many test automation frameworks out there, I haven't found any that deal specifically with benchmarking automation. I found one article that described how to automate one benchmarking tool (fio which we're actually going to use), but it didn't lay out an extensible framework.

By looking at generic automation frameworks and articles about building automated frameworks, I have identified the following key components:

* Have light tests, and a complex framework (rather than the other way around)
* 

### Resources

[javigon: automating fio tests with python](http://javigon.com/2015/04/28/automating-fio-tests-with-python/)
[simpleprogrammer.com: test automation framework architecture](http://simpleprogrammer.com/2014/04/14/test-automation-framework-architecture/)

## Framework Outline

Each test needs to implement output parsing, so that it can be fed to the driver which then can create graphs from the data and stuff...

## Benchmarking Tests

fio, bonnie++, ... (add parameters as well)

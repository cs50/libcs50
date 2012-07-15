############################################################################
Summary: Simplifies user input for C.
Name: library50-c
Version: 17
Release: 0
License: CC BY-NC-SA 3.0
Group: Development/Libraries
Source: %{name}-%{version}.zip
Vendor: CS50
URL: https://manual.cs50.net/Library
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: gcc
BuildArch: i386 x86_64


############################################################################
%define _srcdir /usr/src


############################################################################
# ensure library includes debuginfo
# http://lists.rpm.org/pipermail/rpm-list/2009-January/000127.html
%define debug_package %{nil}
%define __strip /bin/true


############################################################################
# ensure RPM is portable by avoiding rpmlib(FileDigests)
# http://lists.rpm.org/pipermail/rpm-list/2009-October/000401.html
%global _binary_filedigest_algorithm 1
%global _source_filedigest_algorithm 1


############################################################################
# ensure RPM is portable by avoiding rpmlib(PayloadIsXz)
# http://www.cmake.org/pipermail/cmake/2010-March/035580.html
%global _binary_payload w9.gzdio


############################################################################
%description
The CS50 Library for C is a suite of code designed to simplify user input.


############################################################################
%prep
/bin/rm -rf %{_builddir}/%{name}-%{version}/
/usr/bin/unzip %{_sourcedir}/%{name}-%{version}.zip -d %{_builddir}/


############################################################################
%build
/usr/bin/gcc -c -ggdb -std=c99 %{_builddir}/%{name}-%{version}/cs50.c -o %{_builddir}/%{name}-%{version}/cs50.o
/usr/bin/ar rcs %{_builddir}/%{name}-%{version}/libcs50.a %{_builddir}/%{name}-%{version}/cs50.o


############################################################################
%check


############################################################################
%install
/bin/rm -rf %{buildroot}
/bin/mkdir -p %{buildroot}%{_includedir}
/bin/mv %{_builddir}/%{name}-%{version}/cs50.h %{buildroot}%{_includedir}/
/bin/mkdir -p %{buildroot}%{_libdir}
/bin/mv %{_builddir}/%{name}-%{version}/libcs50.a %{buildroot}%{_libdir}/
/bin/mkdir -p %{buildroot}%{_srcdir}
/bin/mv %{_builddir}/%{name}-%{version}/cs50.c %{buildroot}%{_srcdir}/


############################################################################
%clean
rm -rf %{buildroot}


############################################################################
%pre


############################################################################
%post


############################################################################
%preun


############################################################################
%postun


############################################################################
%files
%defattr(0644,root,root,0755)
%{_includedir}/*
%{_libdir}/*
%{_srcdir}/*

%changelog
* Sun Aug 21 2011 David J. Malan <malan@harvard.edu> - 3.0-1
- Initial build

#! /usr/bin/env python3

import xml.etree.ElementTree as ET


def xml2dict(xml_file):
    def f(elem):
        if len(list(elem)) > 0:
            d = {}
            for child in elem:
                    d[child.tag] = f(child)
            return d
        else:
            return elem.text

    tree = ET.parse(xml_file)
    root = tree.getroot()
    d = f(root)
    d = {root.tag: d}
    return d

d = xml2dict('country_data.xml')
print(d)
print(d['data']['country']['rank'])

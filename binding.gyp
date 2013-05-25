{
  "targets": [
    {
      "target_name": "lemur_bindings",
      "include_dirs": ["src"],
      "sources": [
        "src/lemur.cpp",
        "src/midi_output.cpp",
        "src/midi_client.cpp"
      ],
      "conditions": [
        [ 'OS=="mac"', {
            'defines': [
              '__MACOSX_CORE__'
            ],
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            },
            'link_settings': {
              'libraries': [
                'CoreMIDI.framework',
                'CoreAudio.framework',
                'CoreFoundation.framework',
              ],
            }
          }
        ]
      ]
    }
  ]
}
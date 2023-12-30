import { svelte } from '@sveltejs/vite-plugin-svelte';
import { createReadStream, createWriteStream } from 'fs';
import { Transform } from 'stream';
import { defineConfig } from 'vite';
import { viteSingleFile } from "vite-plugin-singlefile";
import { createGzip } from 'zlib';

function createToHex(
  linePrefix: string = '    ',
  columns: number = 16,
  delimiter: string = ',',
  numberPrefix: string = '0x'
): Transform {
  let index = 0;
  return new Transform({
    transform: (chunk: Buffer, encoding: string, done: (error?: Error, data?: any) => void) => {
      var result = '';
      for (let i = 0; i < chunk.length; i++) {
        result += `${index > 0 ? delimiter : ''}${index % columns ? ' ' : (index == 0 ? '' : '\r\n') + linePrefix}${numberPrefix}${chunk[i].toString(16).padStart(2, '0')}`;
        index++;
      }
      done(null, result);
    }
  });
}

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    svelte(),
    viteSingleFile(),
    {
      name: 'postbuild-commands', // the name of your custom plugin. Could be anything.
      closeBundle: async (): Promise<void> => {
        const out = createWriteStream('../src/index_html.h');
        //out.write(`// array size is ${fileData.length / 2}\r\n`)
        out.write('// This file was generated automatically, do not replace content.\r\n\r\n');
        out.write('#pragma once\r\n\r\n');
        out.write('#define index_html_length sizeof(index_html)\r\n');
        out.write('static const byte index_html[] PROGMEM = {\r\n');
        const reads = createReadStream('./dist/index.html');
        const readstr = reads.pipe(createGzip()).pipe(createToHex()).on('end', () => {
          out.write('\r\n};\r\n');
        }).pipe(out);
        //await postBuildCommands() // run during closeBundle hook. https://rollupjs.org/guide/en/#closebundle
      }
    },
  ],
})
